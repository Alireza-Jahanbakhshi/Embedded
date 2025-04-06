/*
 * UART_RS485.c
 *
 * Created: 3/1/2025 7:04:52 AM
 * Author : PA
 */

#define F_CPU 8000000UL // 8 MHz Clock

#include <avr/io.h>
#include <util/delay.h>

#define BAUD 9600
#define MYUBRR F_CPU / 16 / BAUD - 1

#define RS485_DE_RE PD2 // Driver Enable (DE) and Receiver Enable (RE) Pin

void UART_init(uint16_t ubrr)
{
	// Set baud rate
	UBRRH = (uint8_t)(ubrr >> 8);
	UBRRL = (uint8_t)ubrr;

	// Enable receiver and transmitter
	UCSRB = (1 << RXEN) | (1 << TXEN);

	// Set frame format: 8 data, 1 stop bit
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}

void UART_transmit(char data)
{
	while (!(UCSRA & (1 << UDRE)))
		; // Wait for empty transmit buffer
	UDR = data;
}

void UART_send_string(char *str)
{
	while (*str)
	{
		UART_transmit(*str++);
	}
}

char UART_receive(void)
{
	while (!(UCSRA & (1 << RXC)))
		; // Wait for data
	return UDR;
}

void RS485_send(char *message)
{
	PORTD |= (1 << RS485_DE_RE); // Enable transmitter (DE=1, RE=1)
	_delay_ms(1);				 // Allow time for driver enable

	UART_send_string(message);

	_delay_ms(1);				  // Allow time for last bit transmission
	PORTD &= ~(1 << RS485_DE_RE); // Disable transmitter, enable receiver (DE=0, RE=0)
}

int main(void)
{
	UART_init(MYUBRR);

	DDRD |= (1 << RS485_DE_RE);	  // Set DE/RE as output
	PORTD &= ~(1 << RS485_DE_RE); // Start with receiver enabled (DE=0, RE=0)

	_delay_ms(1000);

	while (1)
	{
		RS485_send("Hello RS485\r\n");
		_delay_ms(1000);
	}
}
