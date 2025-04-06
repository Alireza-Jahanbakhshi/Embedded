/*
 * ADC_RegularConv_Polling.c
 *
 * Created: 2/26/2025 11:45:08 PM
 * Author : PA
 */

#define F_CPU 8000000UL // 8 MHz clock

#include <avr/io.h>
#include <util/delay.h>

// Pin definitions for LCD (4-bit mode)
#define LCD_RS PORTB0
#define LCD_E PORTB1
#define LCD_PORT PORTD
#define LCD_DDR DDRD
#define LCD_PORTB PORTB
#define LCD_DDRB DDRB

// LCD commands (4-bit mode)
#define LCD_CLEAR 0x01
#define LCD_HOME 0x02
#define LCD_ENTRY_MODE 0x06
#define LCD_DISPLAY_ON 0x0C
#define LCD_FUNCTION_SET 0x28 // 4-bit, 2 lines, 5x8 font

// ADC definitions
#define ADC_CHANNEL 0 // Using ADC0 (PA0)

// LCD Functions (4-bit mode)
void lcd_command(uint8_t cmd)
{
	PORTB &= ~(1 << LCD_RS);			   // Command mode
	PORTD = (PORTD & 0x0F) | (cmd & 0xF0); // High nibble (D4-D7)
	PORTB |= (1 << LCD_E);
	_delay_us(1);
	PORTB &= ~(1 << LCD_E);
	_delay_us(200);

	PORTD = (PORTD & 0x0F) | ((cmd << 4) & 0xF0); // Low nibble (D4-D7)
	PORTB |= (1 << LCD_E);
	_delay_us(1);
	PORTB &= ~(1 << LCD_E);
	_delay_us(200);
}

void lcd_data(uint8_t data)
{
	PORTB |= (1 << LCD_RS);					// Data mode
	PORTD = (PORTD & 0x0F) | (data & 0xF0); // High nibble (D4-D7)
	PORTB |= (1 << LCD_E);
	_delay_us(1);
	PORTB &= ~(1 << LCD_E);
	_delay_us(200);

	PORTD = (PORTD & 0x0F) | ((data << 4) & 0xF0); // Low nibble (D4-D7)
	PORTB |= (1 << LCD_E);
	_delay_us(1);
	PORTB &= ~(1 << LCD_E);
	_delay_us(200);
}

void lcd_init()
{
	LCD_DDR |= 0xF0;						  // D4-D7 as outputs (4-bit mode)
	LCD_DDRB |= (1 << LCD_RS) | (1 << LCD_E); // RS, E as outputs

	_delay_ms(50); // Wait for LCD power-up

	// Initialize 4-bit mode
	lcd_command(0x33);			   // Reset sequence
	lcd_command(0x32);			   // Set to 4-bit
	lcd_command(LCD_FUNCTION_SET); // 4-bit, 2 lines, 5x8 font
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

// Custom function to convert integer to string for LCD (no sprintf)
void lcd_print_num(uint16_t num)
{
	char buffer[6]; // Max 5 digits for 0-1023 + null terminator
	uint8_t i = 0;

	// Handle the number (0-1023)
	if (num == 0)
	{
		buffer[i++] = '0';
	}
	else
	{
		// Convert to string (right to left)
		while (num > 0 && i < 5)
		{
			buffer[i++] = (num % 10) + '0';
			num /= 10;
		}
		// Add leading spaces to make it 4 digits
		while (i < 4)
		{
			buffer[i++] = ' ';
		}
		buffer[i] = '\0'; // Null terminate

		// Reverse the string in place
		for (uint8_t j = 0; j < i / 2; j++)
		{
			char temp = buffer[j];
			buffer[j] = buffer[i - 1 - j];
			buffer[i - 1 - j] = temp;
		}
	}

	lcd_print(buffer);
}

// ADC Functions
void ADC_Init(void)
{
	ADMUX = (1 << REFS0);											   // Use AVCC as reference
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, prescaler 128
}

uint16_t ADC_Read(uint8_t channel)
{
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // Select channel
	ADCSRA |= (1 << ADSC);					   // Start conversion
	while (ADCSRA & (1 << ADSC))
		;		// Wait for conversion to complete
	return ADC; // Return 10-bit result
}

int main(void)
{
	// Initialize LCD and ADC
	lcd_init();
	ADC_Init();

	// Display initial message
	lcd_command(LCD_HOME); // Move cursor to start
	lcd_print("ADC Value: ");

	while (1)
	{
		uint16_t adc_value = ADC_Read(ADC_CHANNEL); // Read ADC0

		// Move cursor to second line (address 0xC0) and display value
		lcd_command(0xC0); // Second line
		lcd_print_num(adc_value);

		_delay_ms(500); // Update every 500ms
	}

	return 0;
}