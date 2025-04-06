/*
 * USART_RS232.c
 *
 * Created: 3/1/2025 6:57:27 AM
 * Author : PA
 */

#define F_CPU 8000000UL // 8 MHz clock

#include <avr/io.h>
#include <util/delay.h>

// Function to initialize UART
void UART_Init(unsigned int baud)
{
	unsigned int ubrr = F_CPU / 16 / baud - 1;
	UBRRH = (unsigned char)(ubrr >> 8);
	UBRRL = (unsigned char)ubrr;

	UCSRB = (1 << RXEN) | (1 << TXEN);					// Enable receiver and transmitter
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0); // 8-bit data, 1 stop bit, no parity
}

// Function to transmit data
void UART_Transmit(char data)
{
	while (!(UCSRA & (1 << UDRE)))
		;		// Wait until buffer is empty
	UDR = data; // Send data
}

// Function to receive data
char UART_Receive(void)
{
	while (!(UCSRA & (1 << RXC)))
		;		// Wait until data is received
	return UDR; // Return received data
}

// Function to transmit a string
void UART_TransmitString(char *str)
{
	while (*str)
	{
		UART_Transmit(*str);
		str++;
	}
}

int main(void)
{
	UART_Init(9600); // Initialize UART with baud rate of 9600
	_delay_ms(100);	 // Short delay after initialization

	UART_TransmitString("RS232 Test on ATmega16\r\n");

	while (1)
	{
		char receivedChar = UART_Receive(); // Receive a character
		UART_Transmit(receivedChar);		// Echo the received character
	}

	return 0;
}
