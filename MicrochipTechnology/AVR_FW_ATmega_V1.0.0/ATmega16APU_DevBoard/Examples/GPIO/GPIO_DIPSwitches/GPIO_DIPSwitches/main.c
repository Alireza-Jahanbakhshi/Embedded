/*
 * GPIO_DIPSwitches.c
 *
 * Created: 2/27/2025 1:17:13 AM
 * Author : PA
 */

#define F_CPU 8000000UL // 8 MHz clock

#include <avr/io.h>
#include <util/delay.h>

void init_ports(void)
{
	// Configure all PORTA pins as outputs for LEDs
	DDRA = 0xFF;  // All pins (PA0-PA7) as outputs
	PORTA = 0x00; // Initially all LEDs off

	// Configure Port B as input for DIP switch
	DDRB = 0x00;  // All pins as input
	PORTB = 0xF0; // Enable pull-ups on PB0-PB3 (00001111), PB4-PB7 no pull-ups
}

int main(void)
{
	init_ports();

	while (1)
	{
		// Read Port B input from DIP switch
		uint8_t dip_state = PINB;

		// Simple debouncing: check if state is stable
		_delay_ms(10);
		if (dip_state == PINB)
		{ // Confirm reading is stable
			PORTA = ((~dip_state & 0xF0) | (dip_state & 0x0F));
		}
	}

	return 0;
}