/*
 * GPIO_BUZZER.c
 *
 * Created: 2/26/2025 2:05:02 AM
 * Author : PA
 */

#define F_CPU 8000000UL // 8 MHz clock

#include <avr/io.h>		// Standard AVR I/O header
#include <util/delay.h> // Delay functions header

int main(void) // AVR-GCC uses int main(void) instead of void main()
{
	DDRB |= (1 << PB0);	  // Set PB0 as output
	PORTB &= ~(1 << PB0); // Initialize PB0 to low

	while (1)
	{
		PORTB |= (1 << PB0);  // Set PB0 high (buzzer on)
		_delay_ms(500);		  // 500ms delay
		PORTB &= ~(1 << PB0); // Set PB0 low (buzzer off)
		_delay_ms(500);		  // 500ms delay
	}

	return 0; // Never reached, but included for standard compliance
}
