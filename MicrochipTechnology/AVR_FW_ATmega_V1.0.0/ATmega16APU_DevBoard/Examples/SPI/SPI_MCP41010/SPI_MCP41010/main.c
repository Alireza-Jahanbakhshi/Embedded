/*
 * SPI_MCP41010.c
 *
 * Created: 3/1/2025 4:32:10 AM
 * Author : PA
 */

#define F_CPU 8000000UL // 8 MHz clock

#include <avr/io.h>
#include <util/delay.h>

#define CS_PIN PB4	 // Chip Select (SS)
#define MOSI_PIN PB5 // Master Out Slave In
#define SCK_PIN PB7	 // Serial Clock

void SPI_Init()
{
	DDRB |= (1 << MOSI_PIN) | (1 << SCK_PIN) | (1 << CS_PIN); // Set MOSI, SCK, CS as output
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);			  // Enable SPI, Master mode, f/16 (500 kHz SPI speed)
}

void SPI_Write(uint8_t data)
{
	SPDR = data;
	while (!(SPSR & (1 << SPIF)))
		; // Wait for transmission to complete
}

void MCP41010_SetWiper(uint8_t value)
{
	PORTB &= ~(1 << CS_PIN); // Select chip (CS LOW)
	SPI_Write(0b00010001);	 // Command: Write data to potentiometer (0x11)
	SPI_Write(value);		 // Wiper value (0-255)
	PORTB |= (1 << CS_PIN);	 // Deselect chip (CS HIGH)
}

int main()
{
	SPI_Init();

	while (1)
	{

		// Slow reverse cycle (255 ? 0)
		for (uint8_t i = 255; i > 0; i -= 5)
		{ // Slower decrease
			MCP41010_SetWiper(i);
			_delay_ms(200);
		}

		// Forward cycle (0 ? 255)
		for (uint8_t i = 0; i < 255; i += 5)
		{
			MCP41010_SetWiper(i);
			_delay_ms(200);
		}
	}
}
