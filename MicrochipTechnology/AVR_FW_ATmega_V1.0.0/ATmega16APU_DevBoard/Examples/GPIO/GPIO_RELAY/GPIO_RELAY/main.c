/*
 * GPIO_RELAY.c
 *
 * Created: 2/26/2025 2:02:34 AM
 * Author : PA
 */

#define F_CPU 8000000UL // 8 MHz clock

#include <avr/io.h>		// Standard AVR I/O header
#include <util/delay.h> // Delay functions header

int main(void) // AVR-GCC uses int main(void) instead of void main()
{
	PORTB = 0x00; // Initialize PORTB to 0 (all pins low)
	DDRB = 0x01;  // Set PB0 as output (0b00000001), others as inputs

	while (1)
	{
		PORTB ^= (1 << PB0); // Toggle PB0 using XOR operator
		_delay_ms(2000);	 // 2-second delay (2000ms)
	}

	return 0; // Never reached, but included for standard compliance
}
