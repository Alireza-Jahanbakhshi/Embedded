/*
 * UART_PS2_Keyboard.c
 *
 * Created: 3/1/2025 6:52:26 AM
 * Author : PA
 */

#define F_CPU 8000000UL // 8 MHz clock

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define PS2_CLK PD2	 // PS2 Clock on INT0
#define PS2_DATA PD3 // PS2 Data

volatile uint8_t ps2_data = 0;
volatile uint8_t bit_count = 0;
volatile uint8_t received_flag = 0;

ISR(INT0_vect)
{
	static uint8_t shift = 0;

	if (bit_count >= 1 && bit_count <= 8)
	{
		if (PIND & (1 << PS2_DATA))
		{
			ps2_data |= (1 << shift);
		}
		shift++;
	}

	bit_count++;

	if (bit_count == 11)
	{
		received_flag = 1;
		bit_count = 0;
		shift = 0;
	}
}

void PS2_Init()
{
	// Configure PD2 (INT0) as input with pull-up
	DDRD &= ~(1 << PS2_CLK);
	PORTD |= (1 << PS2_CLK);

	// Configure PD3 (DATA) as input with pull-up
	DDRD &= ~(1 << PS2_DATA);
	PORTD |= (1 << PS2_DATA);

	// Enable falling edge interrupt on INT0 (PS2_CLK)
	MCUCR |= (1 << ISC01);
	GICR |= (1 << INT0);

	sei(); // Enable global interrupts
}

void USART_Init(unsigned int baud)
{
	unsigned int ubrr = F_CPU / 16 / baud - 1;
	UBRRH = (unsigned char)(ubrr >> 8);
	UBRRL = (unsigned char)ubrr;
	UCSRB = (1 << TXEN);								// Enable transmitter
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0); // 8-bit data
}

void USART_Transmit(char data)
{
	while (!(UCSRA & (1 << UDRE)))
		; // Wait for empty transmit buffer
	UDR = data;
}

int main()
{
	PS2_Init();
	USART_Init(9600); // Initialize UART for debugging

	while (1)
	{
		if (received_flag)
		{
			received_flag = 0;
			USART_Transmit(ps2_data); // Send received data via UART
		}
	}
}
