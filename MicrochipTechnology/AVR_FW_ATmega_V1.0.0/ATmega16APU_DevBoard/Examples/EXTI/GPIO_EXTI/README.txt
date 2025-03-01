GPIO_EXTI
----------------------------

Description:
This AVR microcontroller program (designed for an 8 MHz clock) demonstrates GPIO configuration with external interrupt (EXTI) handling. It controls three LEDs (PB0, PB1, PB3) using three external interrupts (INT0 on PD2, INT1 on PD3, INT2 on PB2). Each interrupt toggles its corresponding LED when triggered by a falling edge, showcasing interrupt-driven I/O control.

Key Features:
1. GPIO Configuration:
   - Three output LEDs on PORTB (PB0, PB1, PB3)
   - Three input pins with pull-ups (PD2, PD3, PB2)
   - Direct register-level pin manipulation

2. Interrupt System:
   - Uses INT0, INT1, and INT2 external interrupts
   - Configured for falling-edge triggering
   - Individual ISR for each interrupt to toggle LEDs

3. Minimal Main Loop:
   - Simple delay loop to keep CPU active
   - Relies entirely on interrupts for functionality

Connections to Embedded Systems:
1. Hardware Integration:
   - LEDs connected to PB0, PB1, PB3 (PORTB)
   - Interrupt pins PD2 (INT0), PD3 (INT1), PB2 (INT2) for external triggers
   - Pull-up resistors enabled internally, reducing external components
   - Ideal for interfacing with buttons, switches, or sensors

2. Real-Time Response:
   - Interrupt-driven design ensures immediate reaction to events
   - No polling overhead, freeing CPU for other tasks
   - Perfect for event-based embedded applications

3. Resource Utilization:
   - Uses AVR’s built-in interrupt controller
   - Minimal code size with efficient ISR implementations
   - Low power potential with interrupt-based operation

Pros for Embedded Applications:
1. Responsiveness:
   - Instant LED toggling on interrupt triggers
   - No latency from polling loops
   - Suitable for time-critical applications

2. Simplicity:
   - Clean, modular GPIO and EXTI initialization
   - Easy to extend to other pins or interrupt sources
   - Straightforward ISR logic

3. Efficiency:
   - Interrupt-based approach reduces CPU load
   - No continuous polling of input states
   - Lightweight code footprint

Potential Improvements for Embedded Use:
1. Add debouncing logic for mechanical switches
2. Implement sleep modes for power saving
3. Add interrupt priority handling if needed
4. Include LED state feedback or status indicators

Typical Applications:
- Button/switch interfaces for user input
- Sensor event detection (e.g., motion, limit switches)
- Simple control panels or indicators
- Interrupt-driven embedded systems prototyping