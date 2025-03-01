#define F_CPU 8000000UL  // 8 MHz clock
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "diskio.h"
#include "mmc_avr.h"

/* Peripheral controls (Platform dependent) */
#define CS_LOW()    PORTD &= ~(1 << PD4)  /* Set MMC_CS = low (PD4) */
#define CS_HIGH()   PORTD |= (1 << PD4)   /* Set MMC_CS = high (PD4) */
#define MMC_CD      1                     /* Card detected: true */
#define MMC_WP      0                     /* Write protected: false */
#define FCLK_SLOW() SPCR |= (1 << SPR1) | (1 << SPR0)  /* SPI clock ~62.5 kHz (fosc/128) */
#define FCLK_FAST() SPCR &= ~((1 << SPR1) | (1 << SPR0))  /* SPI clock 2 MHz (fosc/4) */

/* MMC/SDC command definitions (unchanged) */
#define CMD0    (0)
#define CMD1    (1)
#define ACMD41  (0x80+41)
#define CMD8    (8)
#define CMD9    (9)
#define CMD10   (10)
#define CMD12   (12)
#define ACMD13  (0x80+13)
#define CMD16   (16)
#define CMD17   (17)
#define CMD18   (18)
#define CMD23   (23)
#define ACMD23  (0x80+23)
#define CMD24   (24)
#define CMD25   (25)
#define CMD32   (32)
#define CMD33   (33)
#define CMD38   (38)
#define CMD48   (48)
#define CMD49   (49)
#define CMD55   (55)
#define CMD58   (58)

static volatile DSTATUS Stat = STA_NOINIT;
static volatile BYTE Timer1;
static volatile UINT Timer2;
static BYTE CardType;

/* Timer0 ISR for 100 Hz decrement */
ISR(TIMER0_COMP_vect) {
	if (Timer1 > 0) Timer1--;
	if (Timer2 > 0) Timer2--;
}

/* Start 100 Hz timer using Timer0 */
void start_timer(void) {
	OCR0 = 77;              // 78 ticks @ 7812.5 Hz = ~10 ms (100 Hz)
	TCCR0 = (1 << WGM01) | (1 << CS02) | (1 << CS00);  // CTC mode, prescaler /1024
	TIMSK |= (1 << OCIE0);  // Enable Timer0 compare interrupt
	sei();                  // Enable global interrupts
}

/* Power on and initialize SPI */
static void power_on(void) {
	_delay_ms(20);  // Wait 20 ms for power stabilization

	/* Configure SPI pins: MOSI (PB5), SCK (PB7), CS (PD4) as outputs, MISO (PB6) as input */
	DDRB |= (1 << PB5) | (1 << PB7);       // MOSI, SCK as outputs
	DDRB &= ~(1 << PB6);                   // MISO as input
	DDRD |= (1 << PD4);                    // CS as output
	PORTD |= (1 << PD4);                   // CS high (deselected)

	/* Enable SPI, Master mode, fosc/4 (2 MHz initially) */
	SPCR = (1 << SPE) | (1 << MSTR);
}

/* Power off and disable SPI */
static void power_off(void) {
	SPCR &= ~(1 << SPE);      // Disable SPI
	PORTD &= ~(1 << PD4);     // CS low (optional, hi-z state)
}

/* Exchange a byte over SPI */
static BYTE xchg_spi(BYTE dat) {
	SPDR = dat;
	while (!(SPSR & (1 << SPIF)));  // Wait for transfer to complete
	return SPDR;
}

/* Receive multiple bytes */
static void rcvr_spi_multi(BYTE *p, UINT cnt) {
	do {
		SPDR = 0xFF;
		while (!(SPSR & (1 << SPIF)));
		*p++ = SPDR;
		SPDR = 0xFF;
		while (!(SPSR & (1 << SPIF)));
		*p++ = SPDR;
	} while (cnt -= 2);
}

/* Send multiple bytes */
static void xmit_spi_multi(const BYTE *p, UINT cnt) {
	do {
		SPDR = *p++;
		while (!(SPSR & (1 << SPIF)));
		SPDR = *p++;
		while (!(SPSR & (1 << SPIF)));
	} while (cnt -= 2);
}

/* Wait for card ready */
static int wait_ready(UINT wt) {
	BYTE d;
	wt /= 10;  // Convert ms to 10 ms units
	cli(); Timer2 = wt; sei();
	do {
		d = xchg_spi(0xFF);
		cli(); wt = Timer2; sei();
	} while (d != 0xFF && wt);
	return (d == 0xFF) ? 1 : 0;
}

/* Deselect card */
static void deselect(void) {
	CS_HIGH();
	xchg_spi(0xFF);  // Dummy clock
}

/* Select card */
static int select(void) {
	CS_LOW();
	xchg_spi(0xFF);  // Dummy clock
	if (wait_ready(500)) return 1;  // Wait up to 500 ms
	deselect();
	return 0;
}

/* Receive data block */
static int rcvr_datablock(BYTE *buff, UINT btr) {
	BYTE token;
	Timer1 = 20;  // 200 ms timeout
	do {
		token = xchg_spi(0xFF);
	} while ((token == 0xFF) && Timer1);
	if (token != 0xFE) return 0;
	rcvr_spi_multi(buff, btr);
	xchg_spi(0xFF);  // Discard CRC
	xchg_spi(0xFF);
	return 1;
}

#if _USE_WRITE
/* Send data block */
static int xmit_datablock(const BYTE *buff, BYTE token) {
	BYTE resp;
	if (!wait_ready(500)) return 0;
	xchg_spi(token);
	if (token == 0xFD) return 1;  // Stop token
	xmit_spi_multi(buff, 512);
	xchg_spi(0xFF);  // Dummy CRC
	xchg_spi(0xFF);
	resp = xchg_spi(0xFF);
	return (resp & 0x1F) == 0x05 ? 1 : 0;
}
#endif

/* Send command */
static BYTE send_cmd(BYTE cmd, DWORD arg) {
	BYTE n, res;
	if (cmd & 0x80) {  // ACMD
		cmd &= 0x7F;
		res = send_cmd(CMD55, 0);
		if (res > 1) return res;
	}
	if (cmd != CMD12) {
		deselect();
		if (!select()) return 0xFF;
	}
	xchg_spi(0x40 | cmd);
	xchg_spi((BYTE)(arg >> 24));
	xchg_spi((BYTE)(arg >> 16));
	xchg_spi((BYTE)(arg >> 8));
	xchg_spi((BYTE)arg);
	n = 0x01;  // Dummy CRC
	if (cmd == CMD0) n = 0x95;
	if (cmd == CMD8) n = 0x87;
	xchg_spi(n);
	if (cmd == CMD12) xchg_spi(0xFF);  // Skip stuff byte
	n = 10;
	do {
		res = xchg_spi(0xFF);
	} while ((res & 0x80) && --n);
	return res;
}

/* Initialize disk */
DSTATUS mmc_disk_initialize(void) {
	BYTE n, cmd, ty, ocr[4];
	start_timer();
	power_off();
	for (Timer1 = 10; Timer1; );  // Wait 100 ms
	if (Stat & STA_NODISK) return Stat;
	power_on();
	FCLK_SLOW();
	for (n = 10; n; n--) xchg_spi(0xFF);  // 80 dummy clocks
	ty = 0;
	if (send_cmd(CMD0, 0) == 1) {
		Timer1 = 100;  // 1 sec timeout
		if (send_cmd(CMD8, 0x1AA) == 1) {  // SDv2?
			for (n = 0; n < 4; n++) ocr[n] = xchg_spi(0xFF);
			if (ocr[2] == 0x01 && ocr[3] == 0xAA) {
				while (Timer1 && send_cmd(ACMD41, 1UL << 30));
				if (Timer1 && send_cmd(CMD58, 0) == 0) {
					for (n = 0; n < 4; n++) ocr[n] = xchg_spi(0xFF);
					ty = (ocr[0] & 0x40) ? CT_SD2 | CT_BLOCK : CT_SD2;
				}
			}
			} else {  // SDv1 or MMC
			if (send_cmd(ACMD41, 0) <= 1) {
				ty = CT_SD1; cmd = ACMD41;
				} else {
				ty = CT_MMC; cmd = CMD1;
			}
			while (Timer1 && send_cmd(cmd, 0));
			if (!Timer1 || send_cmd(CMD16, 512) != 0) ty = 0;
		}
	}
	CardType = ty;
	deselect();
	if (ty) {
		Stat &= ~STA_NOINIT;
		FCLK_FAST();
		} else {
		power_off();
	}
	return Stat;
}

/* Disk status */
DSTATUS mmc_disk_status(void) {
	return Stat;
}

/* Read sector(s) */
DRESULT mmc_disk_read(BYTE *buff, DWORD sector, UINT count) {
	BYTE cmd;
	if (!count) return RES_PARERR;
	if (Stat & STA_NOINIT) return RES_NOTRDY;
	if (!(CardType & CT_BLOCK)) sector *= 512;
	cmd = count > 1 ? CMD18 : CMD17;
	if (send_cmd(cmd, sector) == 0) {
		do {
			if (!rcvr_datablock(buff, 512)) break;
			buff += 512;
		} while (--count);
		if (cmd == CMD18) send_cmd(CMD12, 0);
	}
	deselect();
	return count ? RES_ERROR : RES_OK;
}

#if _USE_WRITE
/* Write sector(s) */
DRESULT mmc_disk_write(const BYTE *buff, DWORD sector, UINT count) {
	if (!count) return RES_PARERR;
	if (Stat & STA_NOINIT) return RES_NOTRDY;
	if (Stat & STA_PROTECT) return RES_WRPRT;
	if (!(CardType & CT_BLOCK)) sector *= 512;
	if (count == 1) {
		if ((send_cmd(CMD24, sector) == 0) && xmit_datablock(buff, 0xFE)) count = 0;
		} else {
		if (CardType & CT_SDC) send_cmd(ACMD23, count);
		if (send_cmd(CMD25, sector) == 0) {
			do {
				if (!xmit_datablock(buff, 0xFC)) break;
				buff += 512;
			} while (--count);
			if (!xmit_datablock(0, 0xFD)) count = 1;
		}
	}
	deselect();
	return count ? RES_ERROR : RES_OK;
}
#endif

#if _USE_IOCTL
/* IOCTL functions (unchanged except for deselect calls) */
DRESULT mmc_disk_ioctl(BYTE cmd, void *buff) {
	DRESULT res;
	BYTE n, csd[16], *ptr = buff;
	DWORD *dp, st, ed, csize;
	if (Stat & STA_NOINIT) return RES_NOTRDY;
	res = RES_ERROR;
	switch (cmd) {
		case CTRL_SYNC:
		if (select()) res = RES_OK;
		deselect();
		break;
		case GET_SECTOR_COUNT:
		if ((send_cmd(CMD9, 0) == 0) && rcvr_datablock(csd, 16)) {
			if ((csd[0] >> 6) == 1) {
				csize = csd[9] + ((WORD)csd[8] << 8) + ((DWORD)(csd[7] & 63) << 16) + 1;
				*(DWORD*)buff = csize << 10;
				} else {
				n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
				csize = (csd[8] >> 6) + ((WORD)csd[7] << 2) + ((WORD)(csd[6] & 3) << 10) + 1;
				*(DWORD*)buff = csize << (n - 9);
			}
			res = RES_OK;
		}
		deselect();
		break;
		case GET_BLOCK_SIZE:
		if (CardType & CT_SD2) {
			if (send_cmd(ACMD13, 0) == 0) {
				xchg_spi(0xFF);
				if (rcvr_datablock(csd, 16)) {
					for (n = 64 - 16; n; n--) xchg_spi(0xFF);
					*(DWORD*)buff = 16UL << (csd[10] >> 4);
					res = RES_OK;
				}
			}
			} else {
			if ((send_cmd(CMD9, 0) == 0) && rcvr_datablock(csd, 16)) {
				if (CardType & CT_SD1) {
					*(DWORD*)buff = (((csd[10] & 63) << 1) + ((WORD)(csd[11] & 128) >> 7) + 1) << ((csd[13] >> 6) - 1);
					} else {
					*(DWORD*)buff = ((WORD)((csd[10] & 124) >> 2) + 1) * (((csd[11] & 3) << 3) + ((csd[11] & 224) >> 5) + 1);
				}
				res = RES_OK;
			}
		}
		deselect();
		break;
		case CTRL_TRIM:
		if (!(CardType & CT_SDC)) break;
		if (mmc_disk_ioctl(MMC_GET_CSD, csd)) break;
		if (!(csd[0] >> 6) && !(csd[10] & 0x40)) break;
		dp = buff; st = dp[0]; ed = dp[1];
		if (!(CardType & CT_BLOCK)) {
			st *= 512; ed *= 512;
		}
		if (send_cmd(CMD32, st) == 0 && send_cmd(CMD33, ed) == 0 && send_cmd(CMD38, 0) == 0 && wait_ready(30000)) {
			res = RES_OK;
		}
		break;
		case MMC_GET_TYPE:
		*ptr = CardType;
		res = RES_OK;
		break;
		case MMC_GET_CSD:
		if (send_cmd(CMD9, 0) == 0 && rcvr_datablock(ptr, 16)) res = RES_OK;
		deselect();
		break;
		case MMC_GET_CID:
		if (send_cmd(CMD10, 0) == 0 && rcvr_datablock(ptr, 16)) res = RES_OK;
		deselect();
		break;
		case MMC_GET_OCR:
		if (send_cmd(CMD58, 0) == 0) {
			for (n = 4; n; n--) *ptr++ = xchg_spi(0xFF);
			res = RES_OK;
		}
		deselect();
		break;
		case MMC_GET_SDSTAT:
		if (send_cmd(ACMD13, 0) == 0) {
			xchg_spi(0xFF);
			if (rcvr_datablock(ptr, 64)) res = RES_OK;
		}
		deselect();
		break;
		case CTRL_POWER_OFF:
		power_off();
		Stat |= STA_NOINIT;
		res = RES_OK;
		break;
		default:
		res = RES_PARERR;
	}
	return res;
}
#endif

/* Timer procedure (called every 10 ms) */
void mmc_disk_timerproc(void) {
	BYTE b;
	UINT n;
	b = Timer1;
	if (b) Timer1 = --b;
	n = Timer2;
	if (n) Timer2 = --n;
	b = Stat;
	if (MMC_WP) b |= STA_PROTECT;
	else b &= ~STA_PROTECT;
	if (MMC_CD) b &= ~STA_NODISK;
	else b |= (STA_NODISK | STA_NOINIT);
	Stat = b;
}