/*
 * RTC_Clock.c
 * Real-Time Clock with 4-digit 7-segment display
 * Created: 2/26/2025
 * Author: PA
 */

#define F_CPU 8000000UL  // 8 MHz system clock
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define A PORTA0
#define B PORTA1
#define C PORTA2
#define D PORTA3
#define E PORTA4
#define F PORTA5
#define G PORTA6
#define DP PORTA7
#define Segment3 PORTB0
#define Segment2 PORTB1
#define Segment1 PORTB2
#define Segment0 PORTB3

void digit_part(int number)
{
	PORTA = (PORTA & 0x00) | (number & 0xFF);  // Set PORTA bits directly
}

void seven_segment(int number, unsigned char segment)
{
	unsigned char data[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
	unsigned char i = 0;
	unsigned char digit[4] = {0};

	// Extract digits (digit[0] = LSD, digit[3] = MSD)
	for (i = 0; i < 4; i++) {
		digit[i] = number % 10;
		number = number / 10;
	}

	// Select segment (map in reverse order)
	PORTB = (PORTB & 0xF0) | (1 << segment);
	
	if (segment < 4) {
		// Reverse the digit mapping: digit[0] to Segment3, digit[3] to Segment0
		unsigned char reversed_segment = 3 - segment;
		digit_part(data[digit[reversed_segment]]);
	}
}

int watch = 0, counter = 0;

ISR(TIMER0_OVF_vect)
{
	static unsigned char digitPoint = 0;
	counter++;
	if (counter == 2)
	{
		counter = 0;
		seven_segment(watch, digitPoint++);
		if (digitPoint >= 4)
		digitPoint = 0;
	}
}

int h = 0, min = 0, s = 0;
ISR(TIMER2_OVF_vect)
{
	s++;
	if (s == 60)
	{
		s = 0;
		min++;
	}
	if (min == 60)
	{
		min = 0;
		h++;
	}
	if (h == 24)
	{
		h = 0;
	}
}

int main(void)
{
	// Port A initialization (all outputs for 7-segment pins)
	DDRA = 0xFF;    // All pins output
	PORTA = 0xFF;   // Initially all high (off for common anode)

	// Port B initialization (PB0-PB3 outputs for segment selection)
	DDRB = (1<<DDB3) | (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
	PORTB = (1<<PORTB3) | (1<<PORTB2) | (1<<PORTB1);  // Start with Segment0 active

	// Timer0 initialization
	// Clock: 8 MHz / 64 = 125 kHz, Period: 2.048 ms
	TCCR0 = (1<<CS01) | (1<<CS00);  // Prescaler 64
	TCNT0 = 0x00;                   // Start at 0
	TIMSK = (1<<TOIE0);             // Enable Timer0 overflow interrupt

	// Timer2 initialization
	// Clock: 32.768 kHz / 128 = 256 Hz, Period: 1 s
	ASSR = (1<<AS2);                // Asynchronous mode (TOSC1 pin, 32.768 kHz crystal)
	TCCR2 = (1<<CS22) | (1<<CS20);  // Prescaler 128
	TCNT2 = 0x00;                   // Start at 0
	TIMSK |= (1<<TOIE2);            // Enable Timer2 overflow interrupt (OR with existing TIMSK)

	sei();  // Enable global interrupts

	while (1)
	{
		// Control decimal point based on active segment (adjusted for reverse SS.MM)
		if (bit_is_set(PORTB, Segment2))  // Segment2 is seconds tens (before minutes)
		PORTA &= ~(1<<DP);    // Clear decimal point for seconds tens
		if (bit_is_set(PORTB, Segment0) || bit_is_set(PORTB, Segment1) || bit_is_set(PORTB, Segment3))
		PORTA |= (1<<DP);     // Set decimal point for others (SS.MM format)
		
		watch = (min * 100) + s;  // Update display value (MMSS format, displayed as SSMM)
	}
	
	return 0;
}