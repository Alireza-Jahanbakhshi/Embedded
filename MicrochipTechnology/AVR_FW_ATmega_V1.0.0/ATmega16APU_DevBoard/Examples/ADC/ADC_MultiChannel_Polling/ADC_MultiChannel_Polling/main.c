/*
 * ADC_MultiChannel_Polling.c
 *
 * Created: 2/26/2025 11:57:29 PM
 * Author : PA
 */ 

#define F_CPU 8000000UL  // 8 MHz clock
#include <avr/io.h>
#include <util/delay.h>

// Pin definitions for LCD (4-bit mode)
#define LCD_RS PORTB0
#define LCD_E  PORTB1
#define LCD_PORT PORTD
#define LCD_DDR  DDRD
#define LCD_PORTB PORTB
#define LCD_DDRB  DDRB

// LCD commands (4-bit mode)
#define LCD_CLEAR 0x01
#define LCD_HOME 0x02
#define LCD_ENTRY_MODE 0x06
#define LCD_DISPLAY_ON 0x0C
#define LCD_FUNCTION_SET 0x28  // 4-bit, 2 lines, 5x8 font

// ADC definitions
#define ADC_VREF_TYPE (1 << REFS0)  // AVCC with external capacitor at AREF

// LCD Functions (4-bit mode, unchanged from your code)
void lcd_command(uint8_t cmd) {
	PORTB &= ~(1 << LCD_RS);  // Command mode
	PORTD = (PORTD & 0x0F) | (cmd & 0xF0);  // High nibble (D4-D7)
	PORTB |= (1 << LCD_E);
	_delay_us(1);
	PORTB &= ~(1 << LCD_E);
	_delay_us(200);
	
	PORTD = (PORTD & 0x0F) | ((cmd << 4) & 0xF0);  // Low nibble (D4-D7)
	PORTB |= (1 << LCD_E);
	_delay_us(1);
	PORTB &= ~(1 << LCD_E);
	_delay_us(200);
}

void lcd_data(uint8_t data) {
	PORTB |= (1 << LCD_RS);  // Data mode
	PORTD = (PORTD & 0x0F) | (data & 0xF0);  // High nibble (D4-D7)
	PORTB |= (1 << LCD_E);
	_delay_us(1);
	PORTB &= ~(1 << LCD_E);
	_delay_us(200);
	
	PORTD = (PORTD & 0x0F) | ((data << 4) & 0xF0);  // Low nibble (D4-D7)
	PORTB |= (1 << LCD_E);
	_delay_us(1);
	PORTB &= ~(1 << LCD_E);
	_delay_us(200);
}

void lcd_init() {
	LCD_DDR |= 0xF0;   // D4-D7 as outputs (PD4-PD7)
	LCD_DDRB |= (1 << LCD_RS) | (1 << LCD_E);  // RS, E as outputs (PB0, PB1)
	
	_delay_ms(50);  // Wait for LCD power-up
	
	// Initialize 4-bit mode
	lcd_command(0x33);  // Reset sequence
	lcd_command(0x32);  // Set to 4-bit
	lcd_command(LCD_FUNCTION_SET);  // 4-bit, 2 lines, 5x8 font
	lcd_command(LCD_DISPLAY_ON);
	lcd_command(LCD_CLEAR);
	lcd_command(LCD_ENTRY_MODE);
	_delay_ms(2);
}

void lcd_print(char *str) {
	while (*str) {
		lcd_data(*str++);
	}
}

void lcd_gotoxy(uint8_t x, uint8_t y) {
	uint8_t address;
	if (y == 0) address = 0x00 + x;  // First line
	else address = 0x40 + x;          // Second line
	lcd_command(0x80 | address);       // Set DDRAM address
}

void lcd_clear() {
	lcd_command(LCD_CLEAR);
	_delay_ms(2);
}

// Custom function to convert unsigned int to string for LCD (avoid sprintf)
void lcd_print_num(uint16_t num, char *buffer, uint8_t max_len) {
	uint8_t i = 0, j;
	
	// Handle the number (0-1023)
	if (num == 0) {
		buffer[i++] = '0';
		} else {
		// Convert to string (right to left)
		while (num > 0 && i < max_len - 1) {
			buffer[i++] = (num % 10) + '0';
			num /= 10;
		}
		// Add leading spaces to make it 4 digits
		while (i < 4) {
			buffer[i++] = ' ';
		}
		buffer[i] = '\0';  // Null terminate
		
		// Reverse the string in place
		for (j = 0; j < i/2; j++) {
			char temp = buffer[j];
			buffer[j] = buffer[i-1-j];
			buffer[i-1-j] = temp;
		}
	}
	
	lcd_print(buffer);  // Display on LCD
}

// Custom function to convert float (temperature) to string for LCD (avoid sprintf)
void lcd_print_float(float value, char *buffer, uint8_t max_len, uint8_t decimals) {
	char temp[10];  // Temporary buffer for integer and decimal parts
	uint8_t i = 0, j;
	int16_t integer_part = (int16_t)value;
	uint16_t decimal_part = (uint16_t)((value - integer_part) * pow(10, decimals));

	// Handle integer part
	if (integer_part < 0) {
		buffer[i++] = '-';
		integer_part = -integer_part;
	}
	if (integer_part == 0) {
		buffer[i++] = '0';
		} else {
		j = 0;
		while (integer_part > 0 && j < 5) {
			temp[j++] = (integer_part % 10) + '0';
			integer_part /= 10;
		}
		while (j > 0) {
			buffer[i++] = temp[--j];
		}
	}

	// Add decimal point and decimal part
	if (decimals > 0) {
		buffer[i++] = '.';
		j = 0;
		while (decimal_part > 0 && j < decimals) {
			temp[j++] = (decimal_part % 10) + '0';
			decimal_part /= 10;
		}
		while (j > 0) {
			buffer[i++] = temp[--j];
		}
	}

	buffer[i] = '\0';  // Null terminate
	lcd_print(buffer);
}

// Helper function to calculate temperature from LM35 ADC value (mV to °C)
float calculate_temperature(uint16_t adc_value) {
	// LM35: 10mV/°C, AVCC = 5V, 10-bit ADC (1023 = 5V)
	float voltage = (adc_value * 5.0) / 1023.0;  // Convert ADC to voltage (V)
	return voltage * 100.0;  // Convert mV to °C (10mV/°C for LM35)
}

// ADC Functions
unsigned int read_adc(unsigned char adc_input)
{
	ADMUX = adc_input | ADC_VREF_TYPE;  // Select channel and reference
	_delay_us(10);  // Delay for ADC input stabilization
	ADCSRA |= (1 << ADSC);  // Start conversion
	while ((ADCSRA & (1 << ADIF)) == 0);  // Wait for conversion to complete
	ADCSRA |= (1 << ADIF);  // Clear ADIF (optional, as reading ADC clears it)
	return ADCW;  // Return 10-bit ADC result
}

void ADC_Init(void) {
	ADMUX = ADC_VREF_TYPE & 0xff;  // AVCC reference
	ADCSRA = 0x87;  // Enable ADC, prescaler 128 (62.5kHz at 8MHz clock)
}

int main(void)
{
	char buffer[17];  // Buffer for LCD display (16 chars + null terminator)
	unsigned int adc0 = 0;  // ADC0 value for LM35 (PA0)
	unsigned int adc1 = 0;  // ADC1 value (e.g., potentiometer, PA1)

	// Initialize ADC and LCD
	ADC_Init();
	lcd_init();

	while (1)
	{
		adc0 = read_adc(0);  // Read from ADC0 (LM35 on PA0)
		adc1 = read_adc(1);  // Read from ADC1 (e.g., potentiometer on PA1)

		float temp = calculate_temperature(adc0);  // Calculate temperature from LM35

		// Clear LCD and position cursor
		lcd_clear();
		lcd_gotoxy(0, 0);  // First line

		// Display temperature from LM35 (e.g., "Temp: 25.5C")
		lcd_print("Temp: ");
		lcd_print_float(temp, buffer, 17, 1);  // Display temperature with 1 decimal place
		lcd_print("C");

		// Move to second line and display ADC1 value
		lcd_gotoxy(0, 1);  // Second line
		lcd_print("ADC1: ");
		lcd_print_num(adc1, buffer, 17);  // Display 4-digit ADC1 value with leading spaces

		_delay_ms(500);  // Update every 500ms
	}
	
	return 0;
}