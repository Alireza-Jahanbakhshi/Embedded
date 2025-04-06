/*
 * TIM_TimeBaseINT.c
 *
 * Created: 2/26/2025 10:32:38 AM
 * Author : PA
 */

#define F_CPU 8000000UL // 8 MHz clock

#include <avr/io.h>
#include <avr/interrupt.h> // For interrupt handling

volatile uint8_t overflow_count = 0; // Volatile because it�s modified in ISR

void Timer0_Init(void)
{
	TCCR0 = (1 << CS02) | (1 << CS00); // Prescaler 1024
	TCNT0 = 0;						   // Start at 0
	TIMSK |= (1 << TOIE0);			   // Enable Timer0 overflow interrupt
	sei();							   // Enable global interrupts
}

ISR(TIMER0_OVF_vect)
{
	overflow_count++;		  // Increment on each overflow
	if (overflow_count >= 15) // ~491.52 ms (15 * 32.768 ms)
	{
		PORTB ^= (1 << PB0); // Toggle PORTB0
		overflow_count = 0;	 // Reset counter
	}
}

int main(void)
{
	DDRB |= (1 << PB0);	  // PORTB0 as output (LED)
	PORTB &= ~(1 << PB0); // Initial state: off

	Timer0_Init(); // Set up Timer0 with interrupt

	while (1)
	{
		// Main loop can do other tasks
		// For this example, it�s empty
	}
}
