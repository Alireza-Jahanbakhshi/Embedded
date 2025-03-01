/*
 * TIM_PWM_L298.c
 *
 * Created: 3/1/2025 6:42:31 AM
 * Author : PA
 */ 
#define F_CPU 8000000UL  // 8 MHz system clock

#include <avr/io.h>
#include <util/delay.h>

// Function to set motor speed using PWM (0-255)
void setMotorSpeed(uint8_t speed) {
	OCR1A = speed; // Set PWM duty cycle
}

// Function to set motor direction
void setMotorDirection(uint8_t dir) {
	if (dir == 1) {  // Forward
		PORTD |= (1 << PD0);
		PORTD &= ~(1 << PD1);
		} else if (dir == 2) {  // Reverse
		PORTD |= (1 << PD1);
		PORTD &= ~(1 << PD0);
		} else {  // Stop
		PORTD &= ~((1 << PD0) | (1 << PD1));
	}
}

// Timer1 PWM Initialization (Fast PWM Mode)
void pwmInit() {
	// Set PB1 (OC1A) as output
	DDRB |= (1 << PB1);

	// Fast PWM Mode, Non-Inverting, Prescaler 64
	TCCR1A = (1 << COM1A1) | (1 << WGM11);
	TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS11) | (1 << CS10);
	
	// Set TOP value for 8-bit resolution
	ICR1 = 255;
}

int main(void) {
	// Set PD0 & PD1 as output for direction control
	DDRD |= (1 << PD0) | (1 << PD1);
	
	// Initialize PWM
	pwmInit();
	
	while (1) {
		// Forward at 70% speed
		setMotorDirection(1);
		setMotorSpeed(178);  // 70% of 255
		_delay_ms(2000);

		// Stop for 1 sec
		setMotorDirection(0);
		_delay_ms(1000);
		
		// Reverse at 50% speed
		setMotorDirection(2);
		setMotorSpeed(127);  // 50% of 255
		_delay_ms(2000);
		
		// Stop for 1 sec
		setMotorDirection(0);
		_delay_ms(1000);
	}
}
