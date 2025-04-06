/*
 * GPIO_InfraredOnLCD.c
 *
 * Created: 2/26/2025 2:10:19 AM
 * Author : PA
 */

#define F_CPU 8000000UL // 8 MHz clock

#include <avr/io.h>		// Standard AVR I/O header
#include <util/delay.h> // Delay functions header
#include <stdio.h>		// For sprintf

// LCD pin definitions (adjust as needed for your hardware)
#define LCD_PORT PORTD
#define LCD_DDR DDRD
#define LCD_RS PD2 // Register Select
#define LCD_EN PD3 // Enable
#define LCD_D4 PD4 // Data 4
#define LCD_D5 PD5 // Data 5
#define LCD_D6 PD6 // Data 6
#define LCD_D7 PD7 // Data 7

// IR detection pin (from P30 on Header 2, assuming connected to PB0)
#define IR_DDR DDRB
#define IR_PORT PORTB
#define IR_PIN PINB
#define IR_INPUT PB0 // IR output from LM358N

// LCD function prototypes
void lcd_init(void);
void lcd_command(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_puts(char *str);
void lcd_gotoxy(unsigned char x, unsigned char y);
void lcd_clear(void);

// Debounce function
void debounce(void);

int main(void)
{
	char array[20];
	int count = 0;

	// GPIO setup
	IR_DDR &= ~(1 << IR_INPUT); // PB0 as input
	IR_PORT |= (1 << IR_INPUT); // Enable pull-up on PB0 (optional, adjust if needed)

	// LCD GPIO setup
	LCD_DDR |= (1 << LCD_RS) | (1 << LCD_EN) |
			   (1 << LCD_D4) | (1 << LCD_D5) |
			   (1 << LCD_D6) | (1 << LCD_D7); // LCD pins as outputs

	// Initialize LCD
	lcd_init();
	lcd_gotoxy(0, 0);
	lcd_puts("IR Detections:");
	lcd_gotoxy(0, 1);
	sprintf(array, "Count: %2d", count);
	lcd_puts(array);

	while (1)
	{
		if (!(IR_PIN & (1 << IR_INPUT))) // If IR detected (active-low, assuming LM358N outputs low)
		{
			debounce();						 // Debounce the input
			if (!(IR_PIN & (1 << IR_INPUT))) // Confirm still low after debounce
			{
				while (!(IR_PIN & (1 << IR_INPUT)))
					;			  // Wait for release
				count++;		  // Increment counter
				lcd_gotoxy(0, 1); // Update second line
				sprintf(array, "Count: %2d", count);
				lcd_puts(array);
			}
		}
	}

	return 0;
}

// LCD functions
void lcd_init(void)
{
	_delay_ms(15);
	lcd_command(0x33);
	_delay_ms(5);
	lcd_command(0x32);
	_delay_ms(1);
	lcd_command(0x28); // 4-bit, 2-line
	lcd_command(0x0C); // Display on, cursor off
	lcd_command(0x06); // Entry mode
	lcd_command(0x01); // Clear display
	_delay_ms(2);
}

void lcd_command(unsigned char cmd)
{
	LCD_PORT &= ~(1 << LCD_RS);
	LCD_PORT &= ~(1 << LCD_EN);
	LCD_PORT = (LCD_PORT & 0x0F) | (cmd & 0xF0);
	LCD_PORT |= (1 << LCD_EN);
	_delay_us(1);
	LCD_PORT &= ~(1 << LCD_EN);
	LCD_PORT = (LCD_PORT & 0x0F) | ((cmd << 4) & 0xF0);
	LCD_PORT |= (1 << LCD_EN);
	_delay_us(1);
	LCD_PORT &= ~(1 << LCD_EN);
	_delay_ms(2);
}

void lcd_data(unsigned char data)
{
	LCD_PORT |= (1 << LCD_RS);
	LCD_PORT &= ~(1 << LCD_EN);
	LCD_PORT = (LCD_PORT & 0x0F) | (data & 0xF0);
	LCD_PORT |= (1 << LCD_EN);
	_delay_us(1);
	LCD_PORT &= ~(1 << LCD_EN);
	LCD_PORT = (LCD_PORT & 0x0F) | ((data << 4) & 0xF0);
	LCD_PORT |= (1 << LCD_EN);
	_delay_us(1);
	LCD_PORT &= ~(1 << LCD_EN);
	_delay_us(100);
}

void lcd_puts(char *str)
{
	while (*str)
		lcd_data(*str++);
}

void lcd_gotoxy(unsigned char x, unsigned char y)
{
	unsigned char address = (y == 0) ? 0x80 + x : 0xC0 + x;
	lcd_command(address);
}

void lcd_clear(void)
{
	lcd_command(0x01);
	_delay_ms(2);
}

// Debounce function for IR sensor
void debounce(void)
{
	_delay_ms(20); // 20ms debounce delay
}