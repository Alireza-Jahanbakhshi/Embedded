/*
* GPIO_InputKeys.c
*
* Created: 2/26/2025 12:14:59 AM
* Author : PA
*/

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0b00000111; // Set PORTB0, PORTB1, PORTB2 as output
	DDRA = 0b00000000; // Set PORTA0, PORTA1, PORTA2 as input
	PORTA = 0b00000111; // Enable pull-up resistors on PORTA0, PORTA1, PORTA2
	PORTB = 0b00000000; // Initialize PORTB to 0 (LEDs off)

	while (1)
	{
		if (!(PINA & (1 << PINA0))) // Check if KEY1 is pressed (active low)
		{
			PORTB = 0b00000001; // Turn on LED1
		}
		else if (!(PINA & (1 << PINA1))) // Check if KEY2 is pressed (active low)
		{
			PORTB = 0b00000010; // Turn on LED2
		}
		else if (!(PINA & (1 << PINA2))) // Check if KEY3 is pressed (active low)
		{
			PORTB = 0b00000100; // Turn on LED3
		}
		else
		{
			PORTB = 0b00000000; // Turn off all LEDs if no key is pressed
		}
	}
}