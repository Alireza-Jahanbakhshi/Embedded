UART_PS2_Mouse
----------------------------

Description:
This AVR microcontroller program (designed for an 8 MHz clock) interfaces with a PS/2 mouse using interrupt-driven input on PD2 (INT0) for the clock and PD3 for data. It captures 3-byte mouse packets (button state/X/Y movement) via an ISR and transmits them over UART at 9600 baud (8N1) with labeled prefixes (B, X, Y). The code includes a basic initialization sequence to enable the mouse.

Key Features:
1. PS/2 Interface:
   - PD2 (INT0) for clock, PD3 for data, both with pull-ups
   - Falling-edge interrupt captures 11-bit frames (start, 8 data, parity, stop)
   - Stores 3-byte packets: buttons, X movement, Y movement

2. UART Configuration:
   - 9600 baud, 8 data bits, no parity, 1 stop bit (8N1)
   - Transmit-only mode on PD1 (TXD)
   - Outputs labeled mouse data (e.g., 'B' + byte)

3. Mouse Control:
   - Basic enable sequence: pulls data low, releases clock
   - Interrupt-driven packet assembly
   - Flags completion of 3-byte packets

Connections to Embedded Systems:
1. Hardware Integration:
   - PS/2 clock (PD2) and data (PD3) to mouse connector
   - UART TX (PD1) to serial terminal/PC
   - Requires PS/2 port with 5V signaling

2. Real-Time Operation:
   - Immediate packet capture via interrupt
   - Asynchronous UART output on packet completion
   - Suitable for mouse tracking systems

3. Resource Utilization:
   - Uses INT0, UART, and 3 I/O pins (PD1, PD2, PD3)
   - Small RAM usage with 3-byte buffer
   - Interrupt-driven for efficiency

Pros for Embedded Applications:
1. Responsiveness:
   - Fast interrupt-based packet capture
   - Low-latency mouse data processing
   - Efficient UART transmission

2. Simplicity:
   - Basic PS/2 mouse protocol handling
   - Clear UART output format
   - Minimal initialization overhead

3. Versatility:
   - Raw packet output for further processing
   - Extensible for mouse command support
   - Good for mouse interfacing projects

Potential Improvements for Embedded Use:
1. Add parity checking for PS/2 data
2. Implement full mouse protocol (e.g., reset, stream mode)
3. Add data interpretation (e.g., movement delta)
4. Include packet buffering

Typical Applications:
- Mouse input for embedded systems
- Serial logging of mouse data
- Custom pointing device interfaces
- Educational projects for interrupts/PS/2/UART