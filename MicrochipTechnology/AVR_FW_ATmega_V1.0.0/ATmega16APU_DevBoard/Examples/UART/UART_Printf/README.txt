UART_Printf
----------------------------

Description:
This AVR microcontroller program (designed for an 8 MHz clock) demonstrates UART communication with printf-style formatted output at 9600 baud (8N1 configuration). It initializes the UART transmitter, redirects stdout to the UART, and continuously prints a counter value (0–99) every second, resetting to 0 after reaching 99.

Key Features:
1. UART Configuration:
   - 9600 baud, 8 data bits, no parity, 1 stop bit (8N1)
   - Baud prescaler: 51 (~0.2% error at 8 MHz)
   - Transmit-only mode enabled

2. Printf Integration:
   - Custom uart_transmit function for stdout
   - Static FILE stream for UART output
   - Formatted string output with counter

3. Operation Logic:
   - Counter increments from 0 to 99, resets at 100
   - 1-second delay between prints
   - Continuous loop with formatted output

Connections to Embedded Systems:
1. Hardware Integration:
   - UART TX (PD1 on ATmega16) to serial terminal/PC
   - Single-pin usage for transmission
   - Typical setup for debugging or logging

2. Real-Time Operation:
   - Periodic 1-second output
   - Consistent baud rate timing
   - Suitable for status reporting

3. Resource Utilization:
   - Uses UART module and 1 I/O pin (PD1)
   - Moderate memory due to printf library
   - Polling-based, no interrupts

Pros for Embedded Applications:
1. Debug Support:
   - Formatted output simplifies debugging
   - Clear counter display via UART
   - Easy to monitor via terminal

2. Simplicity:
   - Straightforward UART setup
   - Minimal code for printf integration
   - Easy to adapt for other data

3. Practicality:
   - Periodic updates every second
   - Reusable UART/printf framework
   - Good for basic communication

Potential Improvements for Embedded Use:
1. Add interrupt-driven UART
2. Implement receive functionality
3. Replace printf with custom formatting
4. Add power-saving modes

Typical Applications:
- Debug output for development
- Status monitoring via serial
- Simple data logging
- Educational projects for UART/printf