/*
* GPIO_IOToggle.c
*
* Created: 2/26/2025 12:02:04 AM
* Author : PA
*/

#define F_CPU 8000000UL  // Define clock frequency (adjust to your setup)
#include <avr/io.h>      // Standard AVR I/O header
#include <util/delay.h>  // AVR delay library

int main(void)
{
	// Set all pins of PORTA, PORTB, PORTC, and PORTD as outputs
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;

	// Initial state: all ports high (0xFF)
	PORTA = 0xFF;
	PORTB = 0xFF;
	PORTC = 0xFF;
	PORTD = 0xFF;

	while (1)
	{
		// PORTA, PORTB, PORTC, PORTD: Blink on/off
		PORTA = 0x00;
		PORTB = 0x00;
		PORTC = 0x00;
		PORTD = 0x00;
		_delay_ms(1000);        // Wait 1 second

		PORTA = 0xFF;
		PORTB = 0xFF;
		PORTC = 0xFF;
		PORTD = 0xFF;
		_delay_ms(1000);        // Wait 1 second
	}

	return 0;  // Never reached due to infinite loop
}
