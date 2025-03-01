/*
 * UART_PS2_Mouse.c
 *
 * Created: 3/1/2025 6:52:59 AM
 * Author : PA
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define PS2_CLK  PD2  // PS/2 Clock connected to INT0
#define PS2_DATA PD3  // PS/2 Data pin

volatile uint8_t mouse_data[3]; // Store 3-byte packets from the mouse
volatile uint8_t bit_count = 0;
volatile uint8_t byte_index = 0;
volatile uint8_t received_flag = 0;

ISR(INT0_vect) {
	static uint8_t shift = 0;
	static uint8_t data_byte = 0;

	if (bit_count >= 1 && bit_count <= 8) {
		if (PIND & (1 << PS2_DATA)) {
			data_byte |= (1 << shift);
		}
		shift++;
	}
	
	bit_count++;

	if (bit_count == 11) {
		mouse_data[byte_index] = data_byte;
		byte_index++;

		if (byte_index == 3) { // Mouse sends 3 bytes per packet
			received_flag = 1;
			byte_index = 0;
		}

		bit_count = 0;
		shift = 0;
		data_byte = 0;
	}
}

void PS2_Init() {
	DDRD &= ~(1 << PS2_CLK);  // Set PD2 as input
	PORTD |= (1 << PS2_CLK);  // Enable pull-up

	DDRD &= ~(1 << PS2_DATA); // Set PD3 as input
	PORTD |= (1 << PS2_DATA); // Enable pull-up

	MCUCR |= (1 << ISC01); // Falling edge trigger for INT0
	GICR |= (1 << INT0);   // Enable INT0

	sei(); // Enable global interrupts
}

void USART_Init(unsigned int baud) {
	unsigned int ubrr = F_CPU / 16 / baud - 1;
	UBRRH = (unsigned char)(ubrr >> 8);
	UBRRL = (unsigned char)ubrr;
	UCSRB = (1 << TXEN);  // Enable transmitter
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0); // 8-bit data
}

void USART_Transmit(char data) {
	while (!(UCSRA & (1 << UDRE)));  // Wait for buffer to be empty
	UDR = data;
}

void Send_Mouse_Data() {
	// First byte contains button states & overflow bits
	USART_Transmit('B');
	USART_Transmit(mouse_data[0]);

	// Second byte (X movement)
	USART_Transmit('X');
	USART_Transmit(mouse_data[1]);

	// Third byte (Y movement)
	USART_Transmit('Y');
	USART_Transmit(mouse_data[2]);
}

void PS2_Mouse_Enable() {
	DDRD |= (1 << PS2_DATA); // Set DATA as output
	PORTD &= ~(1 << PS2_DATA); // Send low signal
	_delay_ms(100);
	
	PORTD |= (1 << PS2_CLK); // Release clock
	_delay_ms(10);
	DDRD &= ~(1 << PS2_DATA); // Set back to input
}

int main() {
	PS2_Init();
	USART_Init(9600);

	_delay_ms(100); // Wait for PS/2 device to stabilize
	PS2_Mouse_Enable(); // Enable the PS/2 mouse

	while (1) {
		if (received_flag) {
			received_flag = 0;
			Send_Mouse_Data(); // Send the data packet via UART
		}
	}
}


