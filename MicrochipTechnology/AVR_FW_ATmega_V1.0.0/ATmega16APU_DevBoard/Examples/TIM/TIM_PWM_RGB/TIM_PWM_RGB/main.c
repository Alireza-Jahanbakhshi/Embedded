/*
 * TIM_PWM_RGB.c
 *
 * Created: 2/26/2025 11:36:13 AM
 * Author : PA
 */ 

#define F_CPU 8000000UL  // Define CPU frequency (8 MHz)
#include <avr/io.h>
#include <util/delay.h>

// Function to initialize PWM
void PWM_Init() {
	// Timer0 for Blue (PB3/OC0)
	TCCR0 = (1 << WGM01) | (1 << WGM00) | (1 << COM01) | (1 << CS01); // Fast PWM, non-inverted, prescaler 8
	DDRB |= (1 << PB3);  // Set PB3 as output

	// Timer1 for Red (PD5/OC1A) and Green (PD4/OC1B)
	TCCR1A = (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1); // 8-bit Fast PWM, non-inverted
	TCCR1B = (1 << WGM12) | (1 << CS11); // Prescaler 8
	DDRD |= (1 << PD5) | (1 << PD4); // Set PD5 and PD4 as outputs
}

// Function to set RGB values (0-255)
void setRGB(uint8_t red, uint8_t green, uint8_t blue) {
	OCR1AL = red;   // Red intensity
	OCR1BL = green; // Green intensity
	OCR0 = blue;    // Blue intensity
}

int main(void) {
	PWM_Init();

	while (1) {
		// Red
		setRGB(255, 0, 0);
		_delay_ms(1000);
		
		// Green
		setRGB(0, 255, 0);
		_delay_ms(1000);
		
		// Blue
		setRGB(0, 0, 255);
		_delay_ms(1000);
		
		// White (all on)
		setRGB(255, 255, 255);
		_delay_ms(1000);
		
		// Off
		setRGB(0, 0, 0);
		_delay_ms(1000);
	}
}
