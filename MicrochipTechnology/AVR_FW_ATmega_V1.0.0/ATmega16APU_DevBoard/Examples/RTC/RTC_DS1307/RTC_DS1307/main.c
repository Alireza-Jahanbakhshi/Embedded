/*
 * RTC_DS1307.c
 *
 * Created: 2/28/2025 2:49:41 PM
 * Author : PA
 */ 


/*
 * RTC_with_UART.c
 * Created: 2/28/2025
 * Author: PA (adapted with Grok 3 assistance)
 */

/*
 * rtc_with_uart.c
 * Created: 2/28/2025
 * Author: PA (adapted with Grok 3 assistance)
 */

#define F_CPU 8000000UL // Define CPU frequency as 8 MHz
#include <avr/io.h>     // AVR I/O header
#include <util/delay.h> // Delay functions
#include <stdio.h>      // For printf

// UART settings (9600 baud, 8N1, 8 MHz clock)
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

// RTC structure for DS1307
typedef struct
{
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t week_day;
    uint8_t date;
    uint8_t month;
    uint8_t year;
} rtc_t;

// DS1307 I2C definitions
#define C_DS1307_READ_MODE_U8  0xD1u
#define C_DS1307_WRITE_MODE_U8 0xD0u
#define C_DS1307_SECOND_REG_ADDRESS_U8 0x00u
#define C_DS1307_CONTROL_REG_ADDRESS_U8 0x07u

// UART transmit function for printf
int uart_transmit(char data, FILE *stream)
{
    while (!(UCSRA & (1 << UDRE))); // Wait for transmit buffer to be empty
    UDR = data;                     // Send character
    return 0;
}

// File stream for UART output
static FILE uart_stream = FDEV_SETUP_STREAM(uart_transmit, NULL, _FDEV_SETUP_WRITE);

// I2C functions
void i2c_init()
{
    TWSR = 0x00; // Prescaler = 1
    TWBR = 0x48; // SCL = 50 kHz at 8 MHz (TWBR = 72)
    TWCR = (1 << TWEN); // Enable TWI
}

void i2c_start()
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

void i2c_stop()
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
    _delay_us(100); // Optional delay
}

void i2c_write(uint8_t i2c_data_u8)
{
    TWDR = i2c_data_u8;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

uint8_t i2c_read(uint8_t ack_option_u8)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (ack_option_u8 << TWEA);
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}

// RTC functions
void rtc_init()
{
    i2c_init();
    i2c_start();
    i2c_write(C_DS1307_WRITE_MODE_U8);
    i2c_write(C_DS1307_CONTROL_REG_ADDRESS_U8);
    i2c_write(0x00); // Disable SQW
    i2c_stop();
}

void rtc_set_date_time(rtc_t *rtc)
{
    i2c_start();
    i2c_write(C_DS1307_WRITE_MODE_U8);
    i2c_write(C_DS1307_SECOND_REG_ADDRESS_U8);
    i2c_write(rtc->sec & 0x7F); // Clear CH bit to start clock
    i2c_write(rtc->min);
    i2c_write(rtc->hour);
    i2c_write(rtc->week_day);
    i2c_write(rtc->date);
    i2c_write(rtc->month);
    i2c_write(rtc->year);
    i2c_stop();
}

void rtc_get_date_time(rtc_t *rtc)
{
    i2c_start();
    i2c_write(C_DS1307_WRITE_MODE_U8);
    i2c_write(C_DS1307_SECOND_REG_ADDRESS_U8);
    i2c_stop();

    i2c_start();
    i2c_write(C_DS1307_READ_MODE_U8);
    rtc->sec = i2c_read(1);
    rtc->min = i2c_read(1);
    rtc->hour = i2c_read(1);
    rtc->week_day = i2c_read(1);
    rtc->date = i2c_read(1);
    rtc->month = i2c_read(1);
    rtc->year = i2c_read(0);
    i2c_stop();
}

int main()
{
    rtc_t rtc;

    // UART initialization (9600 baud, 8N1)
    UBRRH = (uint8_t)(BAUD_PRESCALER >> 8);  // Baud rate high byte
    UBRRL = (uint8_t)(BAUD_PRESCALER);       // Baud rate low byte
    UCSRA = 0x00;                            // No double speed
    UCSRB = (1 << TXEN);                     // Enable transmitter
    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0); // 8-bit, 1 stop, no parity

    // Redirect stdout to UART
    stdout = &uart_stream;

    // Initialize RTC
    rtc_init();

    // Set initial time and date (2:49:41 PM, 28 Feb 2025, Friday)
    rtc.hour = 0x2;    // 2 hours (BCD)
    rtc.min = 0x49;     // 40 minutes (BCD)
    rtc.sec = 0x41;     // 00 seconds (BCD)
    rtc.date = 0x01;    // 28 (BCD)
    rtc.month = 0x02;   // Feb (BCD)
    rtc.year = 0x25;    // 202025 (BCD)
    rtc.week_day = 0x05; // Friday (1 = Mon, 5 = Fri)

    rtc_set_date_time(&rtc); // Set time once, then comment out

    while (1)
    {
        rtc_get_date_time(&rtc);

        // Print time and date via UART in HH:MM:SS DD/MM/YY format
        printf("time: %02x:%02x:%02x  date: %02x/%02x/%02x\r\n",
               rtc.hour, rtc.min, rtc.sec,
               rtc.date, rtc.month, rtc.year);

        _delay_ms(1000); // Update every second
    }
}