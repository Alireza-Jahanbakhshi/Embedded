/*
 * TIM_TimeBase.c
 *
 * Created: 2/26/2025 9:55:36 AM
 * Author : PA
 */

#define F_CPU 8000000UL // 8 MHz clock

#include <avr/io.h>
#include <util/delay.h> // Optional, for delay functions if needed

void Timer0_Init(void)
{
	TCCR0 = (1 << CS02) | (1 << CS00); // Prescaler 1024
	TCNT0 = 0;						   // Start counter at 0
}

int main(void)
{
	DDRB = 0x01;  // Set PORTB0 as output (for LED)
	PORTB = 0x00; // Initial state: LED off

	Timer0_Init(); // Initialize Timer0

	uint8_t overflow_count = 0; // To count overflows

	while (1)
	{
		while ((TIFR & (1 << TOV0)) == 0)
			;				 // Wait for Timer0 overflow
		TIFR |= (1 << TOV0); // Clear overflow flag
		overflow_count++;	 // Increment overflow counter

		if (overflow_count >= 15) // ~491.52 ms (15 * 32.768 ms)
		{
			PORTB ^= 0x01;		// Toggle PORTB0 (LED)
			overflow_count = 0; // Reset counter
		}
	}
}
