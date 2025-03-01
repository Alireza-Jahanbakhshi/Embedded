/*
 * UART_TX_RX.c
 *
 * Created: 2/28/2025 3:14:50 PM
 * Author : PA
 */ 

#define F_CPU 8000000UL    // Define CPU frequency as 8MHz
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

// Function prototypes
void UART_init(void);
void UART_transmit_char(unsigned char data);
unsigned char UART_receive_char(void);
void UART_transmit_string(char *str);
void UART_receive_string(char *buffer, uint8_t max_length);

int main(void)
{
	char receive_buffer[32];    // Buffer to store received string
	UART_init();               // Initialize UART
	
	while(1)
	{
		// Example: Send a string
		UART_transmit_string("Hello from ATmega16!\r\n");
		_delay_ms(1000);
		
		// Receive a string
		UART_receive_string(receive_buffer, 32);
		
		// Echo back the received string
		UART_transmit_string("Received: ");
		UART_transmit_string(receive_buffer);
		UART_transmit_string("\r\n");
		_delay_ms(1000);
	}
	return 0;
}

// Initialize UART
void UART_init(void)
{
	// Set baud rate to 9600 @ 8MHz
	UBRRH = 0;
	UBRRL = 51;    // Changed from 103 to 51 for 8MHz
	
	// Enable receiver and transmitter
	UCSRB = (1<<RXEN) | (1<<TXEN);
	
	// Set frame format: 8 data bits, 1 stop bit, no parity
	UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);
}

// Transmit single character
void UART_transmit_char(unsigned char data)
{
	// Wait for empty transmit buffer
	while(!(UCSRA & (1<<UDRE)));
	// Put data into buffer, sends the data
	UDR = data;
}

// Receive single character
unsigned char UART_receive_char(void)
{
	// Wait for data to be received
	while(!(UCSRA & (1<<RXC)));
	// Get and return received data from buffer
	return UDR;
}

// Transmit string
void UART_transmit_string(char *str)
{
	while(*str != '\0')
	{
		UART_transmit_char(*str);
		str++;
	}
}

// Receive string until newline or buffer full
void UART_receive_string(char *buffer, uint8_t max_length)
{
	uint8_t i = 0;
	char received_char;
	
	while(i < max_length - 1)    // Leave space for null terminator
	{
		received_char = UART_receive_char();
		
		// Check for newline or carriage return
		if(received_char == '\n' || received_char == '\r')
		{
			break;
		}
		
		buffer[i] = received_char;
		i++;
	}
	
	buffer[i] = '\0';    // Add null terminator
}