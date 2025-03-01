/*
* UART_Printf.c
*
* Created: 2/26/2025 3:20:24 AM
* Author : PA
*/

#define F_CPU 8000000UL    // Define CPU frequency (8MHz typical for ATmega16)

#include <avr/io.h>        // Standard AVR I/O header
#include <util/delay.h>    // Delay functions header
#include <stdio.h>         // For printf

// UART settings (9600 baud, 8N1, 8MHz clock)
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

// Function to transmit a character over UART (required for printf)
int uart_transmit(char data, FILE *stream)
{
	while(!(UCSRA & (1 << UDRE)));  // Wait for transmit buffer to be empty
	UDR = data;                      // Send character
	return 0;
}

// File stream for printf (redirect stdout to UART)
static FILE uart_stream = FDEV_SETUP_STREAM(uart_transmit, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
	uint8_t counter = 0;

	// UART initialization (9600 baud, 8N1)
	UBRRH = (uint8_t)(BAUD_PRESCALER >> 8);  // Set baud rate high byte
	UBRRL = (uint8_t)(BAUD_PRESCALER);       // Set baud rate low byte
	UCSRA = 0x00;                            // No double speed (U2X=0)
	UCSRB = (1 << TXEN);                     // Enable transmitter only
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);  // 8 data bits, 1 stop bit, no parity

	// Redirect stdout to UART for printf
	stdout = &uart_stream;

	while(1)
	{
		// Send formatted output using printf
		printf("Counter: %d\r\n", counter);
		counter++;  // Increment counter
		if(counter > 99) counter = 0;  // Reset counter to avoid overflow
		_delay_ms(1000);  // Wait 1 second between sends
	}
	
	return 0;
}
