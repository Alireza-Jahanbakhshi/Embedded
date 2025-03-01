UART_PS2_Keyboard
----------------------------

Description:
This AVR microcontroller program (designed for an 8 MHz clock) interfaces a PS/2 keyboard with an ATmega16 using interrupt-driven input and UART output. It uses PD2 (INT0) as the PS/2 clock and PD3 as the data line, capturing scancodes via an ISR triggered on the falling edge of the clock. Received bytes are sent over UART at 9600 baud (8N1) for debugging or further processing.

Key Features:
1. PS/2 Interface:
   - PD2 (INT0) for clock, PD3 for data, both with pull-ups
   - Falling-edge interrupt on clock to read data bits
   - Captures 11-bit PS/2 frame (start, 8 data, parity, stop)

2. UART Configuration:
   - 9600 baud, 8 data bits, no parity, 1 stop bit (8N1)
   - Transmit-only mode on PD1 (TXD)
   - Outputs raw scancodes as received

3. Interrupt Handling:
   - ISR builds 8-bit scancode from bits 1-8
   - Flags completion after 11 bits
   - Resets for next byte

Connections to Embedded Systems:
1. Hardware Integration:
   - PS/2 clock (PD2) and data (PD3) to keyboard connector
   - UART TX (PD1) to serial terminal/PC
   - Requires PS/2 port or adapter with 5V signaling

2. Real-Time Operation:
   - Immediate scancode capture via interrupt
   - Asynchronous UART output on completion
   - Suitable for keyboard input systems

3. Resource Utilization:
   - Uses INT0, UART, and 3 I/O pins (PD1, PD2, PD3)
   - Minimal RAM with volatile variables
   - Interrupt-driven for efficiency

Pros for Embedded Applications:
1. Responsiveness:
   - Interrupt-based PS/2 reading
   - Low-latency scancode capture
   - Efficient UART output

2. Simplicity:
   - Basic PS/2 protocol handling
   - Easy UART debugging setup
   - Minimal code complexity

3. Versatility:
   - Raw scancode output for processing
   - Extensible for key mapping
   - Good for keyboard interfacing

Potential Improvements for Embedded Use:
1. Add parity checking for PS/2 data
2. Implement scancode-to-ASCII conversion
3. Add keyboard command support (e.g., reset)
4. Include receive buffering

Typical Applications:
- Keyboard input for embedded systems
- Serial debugging of PS/2 devices
- Custom control interfaces
- Educational projects for interrupts/UART