GPIO_KEYPAD_LCD
----------------------------

Description:
This AVR microcontroller program (designed for an 8 MHz clock) interfaces a 4x4 keypad with a 16x2 LCD in 4-bit mode. It uses PORTB for the keypad (PB0-PB3 as rows, PB4-PB7 as columns) and PORTD (PD2-PD7) for the LCD. The code scans the keypad, detects key presses, and displays the corresponding value (0-9, F1-F4, *, #) on the LCD, with numbers on the first line and special characters on the second line after clearing the display.

Key Features:
1. Keypad Configuration:
   - 4x4 matrix on PORTB (rows PB0-PB3, columns PB4-PB7)
   - Rows as outputs, columns as inputs with pull-ups
   - Polling-based scanning with debouncing

2. LCD Interface:
   - 4-bit mode on PORTD (D4-D7 on PD4-PD7, RS on PD2, EN on PD3)
   - Displays numbers as "number=X" on line 1
   - Displays special keys (F1-F4, *, #) on line 2 with clear

3. Input Processing:
   - Returns unique hex values for each key (0x00-0x0F)
   - 20ms debounce delay before and after key press
   - Waits for key release to prevent repeat triggers

Connections to Embedded Systems:
1. Hardware Integration:
   - 4x4 keypad connected to PORTB (8 pins)
   - LCD connected to PORTD (6 pins: PD2-PD7)
   - Pull-ups on columns simplify hardware design
   - Typical setup for user input and display

2. Real-Time Operation:
   - Continuous keypad scanning
   - Immediate LCD updates on key press
   - Suitable for interactive embedded interfaces

3. Resource Utilization:
   - Uses one full port (PORTB) and part of PORTD
   - Moderate memory usage due to sprintf
   - No interrupts, keeping CPU fully available

Pros for Embedded Applications:
1. Usability:
   - Clear visual feedback for all key presses
   - Supports full 4x4 keypad functionality
   - Intuitive display layout for users

2. Robustness:
   - Debouncing ensures reliable key detection
   - Wait-for-release prevents multiple triggers
   - Modular design for keypad and LCD control

3. Flexibility:
   - Keypad mapping easily adjustable
   - LCD functions reusable for other purposes
   - Extensible to more complex input handling

Potential Improvements for Embedded Use:
1. Replace sprintf with custom int-to-string function
2. Add interrupt-driven keypad scanning
3. Implement multi-key press detection
4. Add power-saving sleep modes

Typical Applications:
- Numeric data entry systems
- Menu navigation interfaces
- Security keypads or access controls
- Educational projects for keypad/LCD interfacing