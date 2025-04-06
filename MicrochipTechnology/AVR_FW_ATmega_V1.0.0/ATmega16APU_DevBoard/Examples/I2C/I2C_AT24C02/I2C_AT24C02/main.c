/*
 * I2C_AT24C02.c
 *
 * Created: 3/1/2025 4:18:20 AM
 * Author : PA
 */

#define F_CPU 8000000UL // 8 MHz clock

#include <avr/io.h>
#include <util/delay.h>

// UART Configuration
#define BAUD 9600
#define UBRR_VAL (F_CPU / 16 / BAUD - 1)

// I2C Configuration
#define EEPROM_ADDR 0xA0  // Device address for block 0
#define SCL_FREQ 100000UL // I2C clock frequency = 100kHz

// UART Functions
void UART_init(void)
{
	UBRRH = (UBRR_VAL >> 8); // Set baud rate
	UBRRL = UBRR_VAL;
	UCSRB = (1 << RXEN) | (1 << TXEN);	 // Enable receiver and transmitter
	UCSRC = (1 << URSEL) | (3 << UCSZ0); // 8-bit data, 1 stop bit
}

void UART_transmit(uint8_t data)
{
	while (!(UCSRA & (1 << UDRE)))
		;		// Wait for empty transmit buffer
	UDR = data; // Send data
}

void UART_print(char *str)
{
	while (*str)
	{
		UART_transmit(*str++);
	}
}

void UART_print_hex(uint8_t value)
{
	char hex[] = "0123456789ABCDEF";
	UART_transmit('0');
	UART_transmit('x');
	UART_transmit(hex[value >> 4]);	  // High nibble
	UART_transmit(hex[value & 0x0F]); // Low nibble
}

// TWI/I2C Functions
void TWI_init(void)
{
	TWBR = ((F_CPU / SCL_FREQ) - 16) / 2;
	TWSR = 0x00;
}

void TWI_start(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)))
		;
}

void TWI_stop(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
	while (TWCR & (1 << TWSTO))
		;
}

void TWI_write(uint8_t data)
{
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)))
		;
}

uint8_t TWI_read_nack(void)
{
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)))
		;
	return TWDR;
}

// EEPROM Functions
void EEPROM_write(uint8_t address, uint8_t data)
{
	TWI_start();
	TWI_write(EEPROM_ADDR);
	TWI_write(address);
	TWI_write(data);
	TWI_stop();
	_delay_ms(5);
}

uint8_t EEPROM_read(uint8_t address)
{
	uint8_t data;
	TWI_start();
	TWI_write(EEPROM_ADDR);
	TWI_write(address);
	TWI_start();
	TWI_write(EEPROM_ADDR | 1);
	data = TWI_read_nack();
	TWI_stop();
	return data;
}

int main(void)
{
	// Initialize peripherals
	UART_init();
	TWI_init();

	// Test variables
	uint8_t test_address = 0x10;
	uint8_t test_data = 0xAA;
	uint8_t read_data;

	// Test sequence
	UART_print("EEPROM Test Starting...\n\r");

	// Write test
	UART_print("Writing 0xAA to address 0x10\n\r");
	EEPROM_write(test_address, test_data);

	// Read test
	UART_print("Reading from address 0x10: ");
	read_data = EEPROM_read(test_address);
	UART_print_hex(read_data);
	UART_print("\n\r");

	// Verify
	if (read_data == test_data)
	{
		UART_print("Test Passed: Written and read values match\n\r");
	}
	else
	{
		UART_print("Test Failed: Values don't match\n\r");
	}

	while (1)
	{
		// Main loop
		// Could add more tests or interactive commands here
	}

	return 0;
}
