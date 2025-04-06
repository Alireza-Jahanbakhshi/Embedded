/*
 * WDT_Example.c
 *
 * Created: 2/26/2025 11:43:04 PM
 * Author : PA
 */

#define F_CPU 8000000UL // 8 MHz clock

#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>

// Function to initialize and enable the Watchdog Timer with a 2-second timeout
void WDT_Init(void)
{
	// Enable WDT with 2-second timeout (WDTO_2S)
	// WDTCR configuration: WDE = 1 (Watchdog Enable), WDP2:WDP0 = 110 (2s timeout)
	WDTCR |= (1 << WDE) | (1 << WDP2) | (1 << WDP1);
}

// Function to reset (kick) the Watchdog Timer
void WDT_Reset(void)
{
	wdt_reset(); // Clear the WDT counter
}

int main(void)
{
	// Set up a simple LED output (optional, for demonstration)
	DDRB |= (1 << PB0);	  // Set PB0 as output (LED)
	PORTB &= ~(1 << PB0); // Turn LED off initially

	WDT_Init(); // Initialize and enable WDT

	while (1)
	{
		// Normal operation: Toggle LED and reset WDT every 500ms
		PORTB ^= (1 << PB0); // Toggle LED on PB0
		WDT_Reset();		 // Reset WDT to prevent system reset
		_delay_ms(500);		 // Wait 500ms (must be less than WDT timeout of 2s)
	}

	return 0;
}