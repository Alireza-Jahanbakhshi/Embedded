/*
 * GPIO_EXTI.c
 *
 * Created: 2/26/2025 11:42:25 AM
 * Author : PA
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define LED1 PB0
#define LED2 PB1
#define LED3 PB3

void GPIO_Init() {
	DDRB |= (1 << LED1) | (1 << LED2) | (1 << LED3);    // LEDs as outputs
	PORTB &= ~((1 << LED1) | (1 << LED2) | (1 << LED3)); // LEDs off
	DDRD &= ~((1 << PD2) | (1 << PD3));                 // INT0, INT1 inputs
	DDRB &= ~(1 << PB2);                                // INT2 input
	PORTD |= (1 << PD2) | (1 << PD3);                   // Pull-ups INT0, INT1
	PORTB |= (1 << PB2);                                // Pull-up INT2
}

void EXTI_Init() {
	MCUCR |= (1 << ISC01); MCUCR &= ~(1 << ISC00);      // INT0 falling edge
	MCUCR |= (1 << ISC11); MCUCR &= ~(1 << ISC10);      // INT1 falling edge
	MCUCSR |= (1 << ISC2);                              // INT2 falling edge
	GICR |= (1 << INT0) | (1 << INT1) | (1 << INT2);    // Enable interrupts
	sei();
}

ISR(INT0_vect) { PORTB ^= (1 << LED1); }
ISR(INT1_vect) { PORTB ^= (1 << LED2); }
ISR(INT2_vect) { PORTB ^= (1 << LED3); }

int main(void) {
	GPIO_Init();
	EXTI_Init();
	while (1) { _delay_ms(100); }
}