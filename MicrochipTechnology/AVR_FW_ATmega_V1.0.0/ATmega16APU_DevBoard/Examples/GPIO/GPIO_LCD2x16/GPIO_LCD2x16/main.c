/*
 * GPIO_LCD2x16.c
 *
 * Created: 2/26/2025 1:43:50 AM
 * Author : PA
 */

#define F_CPU 8000000UL // 8 MHz clock

#include <avr/io.h>
#include <util/delay.h>

// Pin definitions
#define LCD_RS PORTB0
#define LCD_E PORTB1
#define LCD_PORT PORTD
#define LCD_DDR DDRD
#define LCD_PORTB PORTB
#define LCD_DDRB DDRB

// LCD commands
#define LCD_CLEAR 0x01
#define LCD_HOME 0x02
#define LCD_ENTRY_MODE 0x06
#define LCD_DISPLAY_ON 0x0C
#define LCD_FUNCTION_SET 0x28 // 4-bit, 2 lines, 5x8 font

void lcd_command(uint8_t cmd)
{
	PORTB &= ~(1 << LCD_RS);			   // Command mode
	PORTD = (PORTD & 0x0F) | (cmd & 0xF0); // High nibble
	PORTB |= (1 << LCD_E);
	_delay_us(1);
	PORTB &= ~(1 << LCD_E);
	_delay_us(200);

	PORTD = (PORTD & 0x0F) | ((cmd << 4) & 0xF0); // Low nibble
	PORTB |= (1 << LCD_E);
	_delay_us(1);
	PORTB &= ~(1 << LCD_E);
	_delay_us(200);
}

void lcd_data(uint8_t data)
{
	PORTB |= (1 << LCD_RS);					// Data mode
	PORTD = (PORTD & 0x0F) | (data & 0xF0); // High nibble
	PORTB |= (1 << LCD_E);
	_delay_us(1);
	PORTB &= ~(1 << LCD_E);
	_delay_us(200);

	PORTD = (PORTD & 0x0F) | ((data << 4) & 0xF0); // Low nibble
	PORTB |= (1 << LCD_E);
	_delay_us(1);
	PORTB &= ~(1 << LCD_E);
	_delay_us(200);
}

void lcd_init()
{
	LCD_DDR |= 0xF0;						  // D4-D7 as outputs
	LCD_DDRB |= (1 << LCD_RS) | (1 << LCD_E); // RS, E as outputs

	_delay_ms(50); // Wait for LCD power-up

	// Initialize 4-bit mode
	lcd_command(0x33); // Reset sequence
	lcd_command(0x32); // Set to 4-bit
	lcd_command(LCD_FUNCTION_SET);
	lcd_command(LCD_DISPLAY_ON);
	lcd_command(LCD_CLEAR);
	lcd_command(LCD_ENTRY_MODE);
	_delay_ms(2);
}

void lcd_print(char *str)
{
	while (*str)
	{
		lcd_data(*str++);
	}
}

int main(void)
{
	lcd_init();
	lcd_print("Hello, ATmega16!");

	while (1)
	{
		// Infinite loop
	}
}
