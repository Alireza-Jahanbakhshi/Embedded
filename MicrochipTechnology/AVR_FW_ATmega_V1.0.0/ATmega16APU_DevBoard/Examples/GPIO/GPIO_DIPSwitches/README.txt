GPIO_DIPSwitches
----------------------------

Description:
This AVR microcontroller program (designed for an 8 MHz clock) demonstrates GPIO interfacing with DIP switches and LEDs. It configures PORTB (PB0-PB7) as inputs to read an 8-bit DIP switch state and PORTA (PA0-PA7) as outputs to control 8 LEDs. The code continuously reads the DIP switch state, applies a simple debounce delay, and mirrors the switch state to the LEDs with an inversion on the upper nibble (PB4-PB7) while keeping the lower nibble (PB0-PB3) direct.

Key Features:
1. GPIO Configuration:
   - PORTA (PA0-PA7) as outputs for 8 LEDs
   - PORTB (PB0-PB7) as inputs for 8 DIP switches
   - Internal pull-ups enabled on PB0-PB3

2. Input Processing:
   - Reads entire PORTB state (8 bits)
   - Basic 10ms debounce delay
   - Bitwise manipulation to control LED output

3. Output Logic:
   - Lower nibble (PB0-PB3) directly mapped to PA0-PA3
   - Upper nibble (PB4-PB7) inverted to PA4-PA7
   - Continuous update in infinite loop

Connections to Embedded Systems:
1. Hardware Integration:
   - 8 LEDs connected to PORTA (PA0-PA7)
   - 8 DIP switches connected to PORTB (PB0-PB7)
   - Pull-ups on PB0-PB3 for stable input (PB4-PB7 assumed grounded when off)
   - Typical setup for user input and visual feedback

2. Real-Time Operation:
   - Continuous polling of DIP switch state
   - Simple debounce for reliable input
   - Direct mapping of inputs to outputs

3. Resource Utilization:
   - Uses two full 8-bit ports efficiently
   - Minimal memory usage with no buffers
   - No interrupts, keeping implementation simple

Pros for Embedded Applications:
1. Simplicity:
   - Straightforward input-to-output mapping
   - Easy to modify for different switch/LED configurations
   - Minimal code size and complexity

2. Practicality:
   - Effective for configuration switches or selectors
   - Visual feedback via LEDs aids debugging
   - Debouncing ensures reliable switch reading

3. Flexibility:
   - Bitwise logic easily adjustable for different mappings
   - Scalable to fewer switches/LEDs if needed
   - Good foundation for control panels or testers

Potential Improvements for Embedded Use:
1. Enhance debouncing with multiple samples
2. Add interrupt-driven input detection
3. Implement power-saving modes
4. Add state change detection to reduce updates

Typical Applications:
- Configuration switches for device settings
- LED-based status or diagnostics displays
- Educational projects for GPIO input/output
- Simple control interfaces for embedded systems