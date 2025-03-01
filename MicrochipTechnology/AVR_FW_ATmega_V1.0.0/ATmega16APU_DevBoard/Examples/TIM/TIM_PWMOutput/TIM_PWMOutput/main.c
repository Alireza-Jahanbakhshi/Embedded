/*
* TIM_PWMOutput.c
*
* Created: 2/26/2025 9:58:38 AM
* Author : PA
*/

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

void Timer1_PWM_Init(void)
{
	DDRD |= (1 << PD5);  // OC1A as output

	// Fast PWM, 10-bit, non-inverting on OC1A
	TCCR1A = (1 << WGM11) | (1 << WGM10) | (1 << COM1A1);
	TCCR1B = (1 << WGM12) | (1 << CS10);  // Prescaler 1
	OCR1A = 0;  // Initial duty cycle
}

int main(void)
{
	Timer1_PWM_Init();

	while (1)
	{
		for (uint16_t duty = 0; duty < 1023; duty += 10)
		{
			OCR1A = duty;
			_delay_ms(10);
		}
		for (uint16_t duty = 1023; duty > 0; duty -= 10)
		{
			OCR1A = duty;
			_delay_ms(10);
		}
	}
}
