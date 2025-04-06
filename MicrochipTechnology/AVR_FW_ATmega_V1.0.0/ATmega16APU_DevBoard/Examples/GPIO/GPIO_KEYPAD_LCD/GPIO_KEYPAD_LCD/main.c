/*
 * GPIO_KEYPAD_LCD.c
 *
 * Created: 2/26/2025 2:31:33 AM
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

// Keypad pin definitions (4x4 matrix)
#define KEY_DDR DDRB
#define KEY_PORT PORTB
#define KEY_PIN PINB
#define R1 PB0 // Row 1
#define R2 PB1 // Row 2
#define R3 PB2 // Row 3
#define R4 PB3 // Row 4
#define C1 PB4 // Column 1
#define C2 PB5 // Column 2
#define C3 PB6 // Column 3
#define C4 PB7 // Column 4

// LCD function prototypes
void lcd_init(void);
void lcd_command(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_puts(char *str);
void lcd_gotoxy(unsigned char x, unsigned char y);
void lcd_clear(void);

// Keypad function prototype
unsigned char Keypad(void);

int main(void)
{
	char show[17] = {0};
	unsigned char kp = 0x80; // Initialize to invalid value

	// GPIO setup for LCD (PORTD)
	LCD_DDR |= (1 << LCD_RS) | (1 << LCD_EN) |
			   (1 << LCD_D4) | (1 << LCD_D5) |
			   (1 << LCD_D6) | (1 << LCD_D7); // LCD pins as outputs

	// GPIO setup for Keypad (PORTB)
	KEY_DDR = 0x0F;	 // PB0-PB3 (rows) as outputs, PB4-PB7 (columns) as inputs
	KEY_PORT = 0xFF; // Enable pull-ups on all PORTB pins

	// Initialize LCD
	lcd_init();
	lcd_clear();

	while (1)
	{
		kp = Keypad();

		if (kp < 0x0A) // Numbers 0-9
		{
			lcd_gotoxy(0, 0);
			sprintf(show, "number=%d", kp);
			lcd_puts(show);
			_delay_ms(500);
		}
		else if (kp == 0x0A) // F1
		{
			lcd_clear();
			lcd_gotoxy(0, 1);
			lcd_puts("f1");
			_delay_ms(500);
		}
		else if (kp == 0x0B) // F2
		{
			lcd_clear();
			lcd_gotoxy(0, 1);
			lcd_puts("f2");
			_delay_ms(500);
		}
		else if (kp == 0x0C) // F3
		{
			lcd_clear();
			lcd_gotoxy(0, 1);
			lcd_puts("f3");
			_delay_ms(500);
		}
		else if (kp == 0x0D) // F4
		{
			lcd_clear();
			lcd_gotoxy(0, 1);
			lcd_puts("f4");
			_delay_ms(500);
		}
		else if (kp == 0x0E) // *
		{
			lcd_clear();
			lcd_gotoxy(0, 1);
			lcd_puts("*");
			_delay_ms(500);
		}
		else if (kp == 0x0F) // #
		{
			lcd_clear();
			lcd_gotoxy(0, 1);
			lcd_puts("#");
			_delay_ms(500);
		}
	}

	return 0;
}

unsigned char Keypad(void)
{
	unsigned char number = 0x80; // Invalid value

	// Row 1 (R1 low, others high)
	KEY_PORT &= ~(1 << R1);						   // R1 = 0
	KEY_PORT |= (1 << R2) | (1 << R3) | (1 << R4); // R2, R3, R4 = 1
	_delay_ms(1);
	if (!(KEY_PIN & (1 << C1)))
	{
		_delay_ms(20);
		while (!(KEY_PIN & (1 << C1)))
			;
		_delay_ms(20);
		number = 0x01;
	} // 1
	if (!(KEY_PIN & (1 << C2)))
	{
		_delay_ms(20);
		while (!(KEY_PIN & (1 << C2)))
			;
		_delay_ms(20);
		number = 0x02;
	} // 2
	if (!(KEY_PIN & (1 << C3)))
	{
		_delay_ms(20);
		while (!(KEY_PIN & (1 << C3)))
			;
		_delay_ms(20);
		number = 0x03;
	} // 3
	if (!(KEY_PIN & (1 << C4)))
	{
		_delay_ms(20);
		while (!(KEY_PIN & (1 << C4)))
			;
		_delay_ms(20);
		number = 0x0A;
	} // F1

	// Row 2 (R2 low, others high)
	KEY_PORT |= (1 << R1);			   // R1 = 1
	KEY_PORT &= ~(1 << R2);			   // R2 = 0
	KEY_PORT |= (1 << R3) | (1 << R4); // R3, R4 = 1
	_delay_ms(1);
	if (!(KEY_PIN & (1 << C1)))
	{
		_delay_ms(20);
		while (!(KEY_PIN & (1 << C1)))
			;
		_delay_ms(20);
		number = 0x04;
	} // 4
	if (!(KEY_PIN & (1 << C2)))
	{
		_delay_ms(20);
		while (!(KEY_PIN & (1 << C2)))
			;
		_delay_ms(20);
		number = 0x05;
	} // 5
	if (!(KEY_PIN & (1 << C3)))
	{
		_delay_ms(20);
		while (!(KEY_PIN & (1 << C3)))
			;
		_delay_ms(20);
		number = 0x06;
	} // 6
	if (!(KEY_PIN & (1 << C4)))
	{
		_delay_ms(20);
		while (!(KEY_PIN & (1 << C4)))
			;
		_delay_ms(20);
		number = 0x0B;
	} // F2

	// Row 3 (R3 low, others high)
	KEY_PORT |= (1 << R1) | (1 << R2); // R1, R2 = 1
	KEY_PORT &= ~(1 << R3);			   // R3 = 0
	KEY_PORT |= (1 << R4);			   // R4 = 1
	_delay_ms(1);
	if (!(KEY_PIN & (1 << C1)))
	{
		_delay_ms(20);
		while (!(KEY_PIN & (1 << C1)))
			;
		_delay_ms(20);
		number = 0x07;
	} // 7
	if (!(KEY_PIN & (1 << C2)))
	{
		_delay_ms(20);
		while (!(KEY_PIN & (1 << C2)))
			;
		_delay_ms(20);
		number = 0x08;
	} // 8
	if (!(KEY_PIN & (1 << C3)))
	{
		_delay_ms(20);
		while (!(KEY_PIN & (1 << C3)))
			;
		_delay_ms(20);
		number = 0x09;
	} // 9
	if (!(KEY_PIN & (1 << C4)))
	{
		_delay_ms(20);
		while (!(KEY_PIN & (1 << C4)))
			;
		_delay_ms(20);
		number = 0x0C;
	} // F3

	// Row 4 (R4 low, others high)
	KEY_PORT |= (1 << R1) | (1 << R2) | (1 << R3); // R1, R2, R3 = 1
	KEY_PORT &= ~(1 << R4);						   // R4 = 0
	_delay_ms(1);
	if (!(KEY_PIN & (1 << C1)))
	{
		_delay_ms(20);
		while (!(KEY_PIN & (1 << C1)))
			;
		_delay_ms(20);
		number = 0x0E;
	} // *
	if (!(KEY_PIN & (1 << C2)))
	{
		_delay_ms(20);
		while (!(KEY_PIN & (1 << C2)))
			;
		_delay_ms(20);
		number = 0x00;
	} // 0
	if (!(KEY_PIN & (1 << C3)))
	{
		_delay_ms(20);
		while (!(KEY_PIN & (1 << C3)))
			;
		_delay_ms(20);
		number = 0x0F;
	} // #
	if (!(KEY_PIN & (1 << C4)))
	{
		_delay_ms(20);
		while (!(KEY_PIN & (1 << C4)))
			;
		_delay_ms(20);
		number = 0x0D;
	} // F4

	return number;
}

// LCD functions (reused from previous responses)
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
