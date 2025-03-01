GPIO_InputKeys
----------------------------

Description:
This AVR microcontroller program (designed for an 8 MHz clock) demonstrates GPIO-based input handling with output control. It configures three pins on PORTA (PA0-PA2) as inputs with pull-ups to read key presses and three pins on PORTB (PB0-PB2) as outputs to control LEDs. The code continuously polls the input pins and lights a corresponding LED when a key is pressed (active-low), turning off all LEDs when no key is pressed.

Key Features:
1. GPIO Configuration:
   - PA0-PA2 as inputs with internal pull-ups
   - PB0-PB2 as outputs for LEDs
   - Direct register manipulation using bit masks

2. Input Handling:
   - Polling-based detection of three keys
   - Active-low logic (pressed = 0)
   - Mutually exclusive LED control

3. Output Control:
   - One LED per key (PB0 for PA0, PB1 for PA1, PB2 for PA2)
   - All LEDs off when no key is pressed
   - Simple if-else priority structure

Connections to Embedded Systems:
1. Hardware Integration:
   - Keys/buttons connected to PA0-PA2 (PORTA)
   - LEDs connected to PB0-PB2 (PORTB)
   - Pull-ups eliminate need for external resistors
   - Common setup for user input interfaces

2. Real-Time Operation:
   - Continuous polling for immediate response
   - Direct mapping of inputs to outputs
   - Suitable for simple control applications

3. Resource Utilization:
   - Uses only 3 input and 3 output pins
   - Minimal code size with no external libraries
   - No interrupts, keeping implementation lightweight

Pros for Embedded Applications:
1. Simplicity:
   - Easy to understand and implement
   - Clear input-output relationship
   - Minimal setup for basic key control

2. Efficiency:
   - Low resource usage (6 pins total)
   - No complex logic or timing requirements
   - Fast polling