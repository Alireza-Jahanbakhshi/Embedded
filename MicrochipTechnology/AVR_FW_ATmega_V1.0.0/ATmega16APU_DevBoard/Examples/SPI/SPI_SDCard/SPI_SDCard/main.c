/*
 * SPI_SDCard.c
 *
 * Created: 3/1/2025 7:09:41 AM
 * Author : PA
 */ 

#define F_CPU 8000000UL  // 8 MHz internal clock
#include <avr/io.h>
#include <util/delay.h>

// SPI Pins (ATmega16)
#define SPI_DDR  DDRB
#define SPI_PORT PORTB
#define SS       PB4  // Chip Select for SD card
#define MOSI     PB5
#define MISO     PB6
#define SCK      PB7

// UART Pins (ATmega16)
#define UART_DDR  DDRD
#define UART_PORT PORTD
#define RXD       PD0
#define TXD       PD1
#define LED       PD2  // Status LED

// SD Card Commands
#define GO_IDLE_STATE       0
#define SEND_OP_COND        1
#define SEND_CSD            9
#define SET_BLOCK_LEN       16
#define READ_SINGLE_BLOCK   17
#define WRITE_SINGLE_BLOCK  24
#define ERASE_BLOCK_START   32
#define ERASE_BLOCK_END     33
#define ERASE_SELECTED      38

// Buffer for SD card block (512 bytes)
volatile unsigned char buffer[512];
volatile unsigned long startBlock;
volatile unsigned long totalBlocks;

// Function Declarations (fixes implicit declaration issue)
void port_init(void);
void spi_init(void);
void spi_high_speed(void);
unsigned char spi_transmit(unsigned char data);
void uart_init(void);
void uart_transmit(unsigned char data);
unsigned char uart_receive(void);
void uart_transmit_string(const char *str);
void uart_newline(void);
unsigned char sd_init(void);
unsigned char sd_send_command(unsigned char cmd, unsigned long arg);
unsigned char sd_read_single_block(unsigned long block);
unsigned char sd_write_single_block(unsigned long block);
unsigned char sd_erase(unsigned long start, unsigned long total);

// Port Initialization
void port_init(void)
{
    // SPI: PB4 (SS), PB5 (MOSI), PB7 (SCK) outputs; PB6 (MISO) input
    SPI_DDR  = (1 << SS) | (1 << MOSI) | (1 << SCK);  // Outputs
    SPI_PORT = (1 << SS) | (1 << MISO);              // SS high, MISO pull-up

    // UART: PD0 (RXD) input, PD1 (TXD) output; PD2 (LED) output
    UART_DDR  = (1 << TXD) | (1 << LED);  // TXD and LED outputs
    UART_PORT = (1 << RXD);               // RXD pull-up
}

// SPI Initialization (Master, 125 kHz initially)
void spi_init(void)
{
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);  // Enable SPI, Master, fosc/128
    SPSR = 0;  // No double speed yet
}

// SPI High Speed (4 MHz)
void spi_high_speed(void)
{
    SPCR = (1 << SPE) | (1 << MSTR);  // fosc/4 (2 MHz, adjust if needed)
    SPSR = (1 << SPI2X);              // Double speed to 4 MHz
}

// SPI Transmit/Receive Byte
unsigned char spi_transmit(unsigned char data)
{
    SPDR = data;
    while (!(SPSR & (1 << SPIF)));  // Wait for transmission complete
    return SPDR;                    // Return received byte
}

// UART Initialization (19200 baud @ 8 MHz)
void uart_init(void)
{
    UBRRH = 0x00;                   // Baud rate high byte
    UBRRL = 25;                     // Baud rate low byte (19231, 0.2% error)
    UCSRA = 0x00;
    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);  // 8-bit data
    UCSRB = (1 << RXEN) | (1 << TXEN);                   // Enable RX and TX
}

// UART Transmit Byte
void uart_transmit(unsigned char data)
{
    while (!(UCSRA & (1 << UDRE)));  // Wait for empty transmit buffer
    UDR = data;                      // Send data
}

// UART Receive Byte
unsigned char uart_receive(void)
{
    while (!(UCSRA & (1 << RXC)));  // Wait for data
    return UDR;                     // Return received byte
}

// Transmit String
void uart_transmit_string(const char *str)
{
    while (*str)
        uart_transmit(*str++);
}

// Transmit Newline
void uart_newline(void)
{
    uart_transmit('\r');
    uart_transmit('\n');
}

// SD Card Chip Select Macros
#define SD_CS_ASSERT   SPI_PORT &= ~(1 << SS)
#define SD_CS_DEASSERT SPI_PORT |= (1 << SS)

// SD Card Initialization
unsigned char sd_init(void)
{
    unsigned char i, response, retry = 0;

    SD_CS_DEASSERT;
    _delay_ms(1);  // Power-on delay

    // Send 80 clock cycles with CS high
    for (i = 0; i < 10; i++)
        spi_transmit(0xFF);

    SD_CS_ASSERT;
    do {
        response = sd_send_command(GO_IDLE_STATE, 0);  // CMD0
        retry++;
        if (retry > 200) return 1;  // Timeout
    } while (response != 0x01);

    retry = 0;
    do {
        response = sd_send_command(SEND_OP_COND, 0);  // CMD1
        retry++;
        if (retry > 200) return 1;  // Timeout
    } while (response != 0x00);

    sd_send_command(SET_BLOCK_LEN, 512);  // CMD16, set block size to 512
    SD_CS_DEASSERT;

    return 0;  // Success
}

// Send SD Card Command
unsigned char sd_send_command(unsigned char cmd, unsigned long arg)
{
    unsigned char response, retry = 0;

    SD_CS_ASSERT;
    spi_transmit(cmd | 0x40);  // Command with start bits (01xxxxxx)
    spi_transmit(arg >> 24);   // Argument bytes
    spi_transmit(arg >> 16);
    spi_transmit(arg >> 8);
    spi_transmit(arg);
    spi_transmit(0x95);        // CRC (hardcoded for CMD0, ignored later)

    while ((response = spi_transmit(0xFF)) == 0xFF) {
        if (retry++ > 200) break;  // Timeout
    }

    SD_CS_DEASSERT;
    spi_transmit(0xFF);  // Extra 8 clocks
    return response;
}

// Read Single Block
unsigned char sd_read_single_block(unsigned long block)
{
    unsigned char response;
    unsigned int i, retry = 0;

    response = sd_send_command(READ_SINGLE_BLOCK, block << 9);  // Convert to byte address
    if (response != 0x00) return response;

    SD_CS_ASSERT;
    while (spi_transmit(0xFF) != 0xFE) {  // Wait for data token
        if (retry++ > 5000) {
            SD_CS_DEASSERT;
            return 1;
        }
    }

    for (i = 0; i < 512; i++)  // Read 512 bytes
        buffer[i] = spi_transmit(0xFF);

    spi_transmit(0xFF);  // Dummy CRC
    spi_transmit(0xFF);
    SD_CS_DEASSERT;

    return 0;
}

// Write Single Block
unsigned char sd_write_single_block(unsigned long block)
{
    unsigned char response;
    unsigned int i, retry = 0;

    response = sd_send_command(WRITE_SINGLE_BLOCK, block << 9);
    if (response != 0x00) return response;

    SD_CS_ASSERT;
    spi_transmit(0xFE);  // Start token

    for (i = 0; i < 512; i++)  // Write 512 bytes
        spi_transmit(buffer[i]);

    spi_transmit(0xFF);  // Dummy CRC
    spi_transmit(0xFF);

    response = spi_transmit(0xFF);
    if ((response & 0x1F) != 0x05) {  // Data accepted?
        SD_CS_DEASSERT;
        return response;
    }

    while (spi_transmit(0xFF) == 0) {  // Wait for write to finish
        if (retry++ > 5000) {
            SD_CS_DEASSERT;
            return 1;
        }
    }

    SD_CS_DEASSERT;
    return 0;
}

// Erase Blocks
unsigned char sd_erase(unsigned long start, unsigned long total)
{
    unsigned char response;

    response = sd_send_command(ERASE_BLOCK_START, start << 9);
    if (response != 0x00) return response;

    response = sd_send_command(ERASE_BLOCK_END, (start + total - 1) << 9);
    if (response != 0x00) return response;

    response = sd_send_command(ERASE_SELECTED, 0);
    if (response != 0x00) return response;

    return 0;
}

// Main Program
int main(void)
{
    unsigned char option, data, error;
    unsigned int i;

    port_init();
    spi_init();
    uart_init();

    _delay_ms(100);  // VCC stabilization
    UART_PORT |= (1 << LED);  // LED on

    uart_transmit_string("ATmega16 SD Card Test\r\n");
    if (sd_init() == 0) {
        uart_transmit_string("SD Card Initialized\r\n");
        spi_high_speed();  // Switch to 4 MHz SPI
    } else {
        uart_transmit_string("SD Init Failed\r\n");
        while (1);  // Halt
    }

    while (1) {
        uart_transmit_string("\r\nMenu:\r\n");
        uart_transmit_string("0: Erase Blocks\r\n");
        uart_transmit_string("1: Write Single Block\r\n");
        uart_transmit_string("2: Read Single Block\r\n");
        uart_transmit_string("Select (0-2): ");

        option = uart_receive();
        uart_transmit(option);
        uart_newline();

        if (option >= '0' && option <= '2') {
            uart_transmit_string("Enter Block (0-9999): ");
            startBlock = 0;
            for (i = 0; i < 4; i++) {
                data = uart_receive();
                uart_transmit(data);
                startBlock = startBlock * 10 + (data - '0');
            }
            uart_newline();
        }

        switch (option) {
            case '0':
                uart_transmit_string("Blocks to Erase (1-999): ");
                totalBlocks = 0;
                for (i = 0; i < 3; i++) {
                    data = uart_receive();
                    uart_transmit(data);
                    totalBlocks = totalBlocks * 10 + (data - '0');
                }
                uart_newline();
                error = sd_erase(startBlock, totalBlocks);
                if (error) uart_transmit_string("Erase Failed\r\n");
                else uart_transmit_string("Erase OK\r\n");
                break;

            case '1':
                uart_transmit_string("Enter 512 bytes (end with ~): ");
                i = 0;
                do {
                    data = uart_receive();
                    uart_transmit(data);
                    buffer[i++] = data;
                } while (data != '~' && i < 512);
                for (; i < 512; i++) buffer[i] = 0;  // Pad with zeros
                error = sd_write_single_block(startBlock);
                if (error) uart_transmit_string("Write Failed\r\n");
                else uart_transmit_string("Write OK\r\n");
                break;

            case '2':
                error = sd_read_single_block(startBlock);
                if (error) {
                    uart_transmit_string("Read Failed\r\n");
                } else {
                    uart_transmit_string("Data: ");
                    for (i = 0; i < 512 && buffer[i] != '~'; i++)
                        uart_transmit(buffer[i]);
                    uart_transmit_string("\r\nRead OK\r\n");
                }
                break;

            default:
                uart_transmit_string("Invalid Option\r\n");
        }
    }

    return 0;
}
