/*
* GPIO_RGB.c
*
* Created: 2/26/2025 1:59:48 AM
* Author : PA
*/

#define F_CPU 8000000UL    // Define CPU frequency (8MHz typical for ATmega16)

#include <avr/io.h>        // Standard AVR I/O header
#include <util/delay.h>    // Delay functions header

int main(void)
{
	uint8_t i = 0;
	DDRB = 0x07;       // Set PB0-PB2 as outputs for RGB

	while(1)
	{
		PORTB = i;     // Output to GPIO pins PB0-PB2
		_delay_ms(500); // 500ms delay
		i++;
		if(i == 7)     // After 0b110 (6)
		i = 0;     // Reset to 0
	}
	
	return 0;
}
