/*
 * GPIO_STEPPER.c
 * Created: 2/26/2025 2:59:04 AM
 * Author: PA
 */

#define F_CPU 8000000UL    // Define CPU frequency (8MHz typical for ATmega16)
#include <avr/io.h>
#include <util/delay.h>

#define STEP_PORT PORTC    // Port connected to ULN2003
#define STEP_DDR  DDRC     // Data Direction Register for step port

// Define stepper motor sequence for full-step drive
const uint8_t step_sequence[4] = {0b00001000, 0b00000100, 0b00000010, 0b00000001};

void stepper_step(uint8_t step) {
    STEP_PORT = step_sequence[step]; // Output step pattern
}

// Variable delay function
void delay_variable_ms(int delay_ms) {
    while (delay_ms--) {
        _delay_loop_2(2000); // Approximate 1ms delay for 8MHz clock
    }
}

void stepper_rotate(int steps, int delay_ms, uint8_t direction) {
    for (int i = 0; i < steps; i++) {
        if (direction == 1) {
            stepper_step(i % 4); // Clockwise
        } else {
            stepper_step((3 - (i % 4))); // Counterclockwise
        }

        delay_variable_ms(delay_ms); // Use loop-based delay
    }
}

int main(void) {
    STEP_DDR = 0x0F; // Set lower 4 bits of PORTC as output

    while (1) {
        stepper_rotate(200, 10, 1); // Rotate clockwise
        _delay_ms(1000);  // Pause

        stepper_rotate(200, 10, 0); // Rotate counterclockwise
        _delay_ms(1000);  // Pause
    }

    return 0;
}
