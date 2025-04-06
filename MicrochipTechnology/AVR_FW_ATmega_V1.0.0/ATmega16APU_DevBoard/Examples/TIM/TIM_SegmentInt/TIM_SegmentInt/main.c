/*
 * TIM_SegmentInt.c
 *
 * Created: 2/26/2025 10:36:33 AM
 * Author : PA
 */

#define F_CPU 8000000UL // 8 MHz clock

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Segment pin definitions on PORTA
#define A (PORTA & (1 << PA0))
#define B (PORTA & (1 << PA1))
#define C (PORTA & (1 << PA2))
#define D (PORTA & (1 << PA3))
#define E (PORTA & (1 << PA4))
#define F (PORTA & (1 << PA5))
#define G (PORTA & (1 << PA6))
#define DP (PORTA & (1 << PA7))

// Digit select pins on PORTB
#define Segment3 (PORTB & (1 << PB0))
#define Segment2 (PORTB & (1 << PB1))
#define Segment1 (PORTB & (1 << PB2))
#define Segment0 (PORTB & (1 << PB3))

// Set segment pins for a digit
void digit_part(uint8_t number)
{
	PORTA = number; // Directly set PORTA with the segment pattern
}

// Display a number on a specific 7-segment digit
void seven_segment(int number, uint8_t segment)
{
	// Common-anode 7-segment codes (0 = on, 1 = off)
	const uint8_t data[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
	uint8_t digit[4] = {0};
	uint8_t i;

	// Extract digits from number
	for (i = 0; i < 4; i++)
	{
		digit[i] = number % 10;
		number /= 10;
	}

	// Select the active digit (set high, others low)
	PORTB &= ~(0x0F); // Clear PB0�PB3
	switch (segment)
	{
	case 0:
		PORTB |= (1 << PB3); // Segment0
		break;
	case 1:
		PORTB |= (1 << PB2); // Segment1
		break;
	case 2:
		PORTB |= (1 << PB1); // Segment2
		break;
	case 3:
		PORTB |= (1 << PB0); // Segment3
		break;
	}

	// Display the digit if segment is valid
	if (segment < 4)
	{
		digit_part(data[digit[segment]]);
	}
}

// Timer2 overflow interrupt service routine
volatile int number = 0;

ISR(TIMER2_OVF_vect)
{
	static uint8_t digitPoint = 0;
	seven_segment(number, digitPoint++);
	if (digitPoint >= 4)
	{
		digitPoint = 0;
	}
	TCNT2 = 255 - 250; // Preload for ~1 ms overflow
}

int main(void)
{
	// PORTA: All outputs for segments (A�G, DP)
	DDRA = 0xFF;  // All pins output
	PORTA = 0xFF; // Initial state: all segments off (common-anode)

	// PORTB: PB0�PB3 outputs for digit select, PB4 input for button
	DDRB = 0x0F;  // PB0�PB3 outputs, PB4�PB7 inputs
	PORTB = 0x1F; // PB0�PB3 high (off), PB4 pull-up enabled

	// Timer2: Normal mode, prescaler 32 (~1 ms overflow with preload)
	TCCR2 = (1 << CS21) | (1 << CS20); // Prescaler 32
	TCNT2 = 255 - 250;				   // Preload for 1 ms (see below)
	TIMSK = (1 << TOIE2);			   // Enable Timer2 overflow interrupt

	// Enable global interrupts
	sei();

	while (1)
	{
		// Check button on PB4 (active low)
		if (!(PINB & (1 << PB4)))
		{
			_delay_ms(50); // Debounce
			while (!(PINB & (1 << PB4)))
				; // Wait for release
			number++;
			if (number >= 10000)
			{
				number = 0;
			}
		}
	}
}
