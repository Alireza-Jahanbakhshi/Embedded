TIM_SegmentInt
----------------------------

Description:
This AVR microcontroller program (designed for an 8 MHz clock) displays a 4-digit counter (0–9999) on a 7-segment display using Timer2 interrupts for multiplexing. PORTA drives the segment lines (A–G, DP), and PORTB (PB0–PB3) selects the digits. A button on PB4 increments the counter, with debouncing. Timer2 runs at a ~1 ms overflow rate (8 MHz / 32 / 250) for a ~250 Hz refresh per digit.

Key Features:
1. Display Configuration:
   - PORTA (PA0–PA7) for segments (common-anode, low = on)
   - PORTB (PB0–PB3) for digit selection (high = active)
   - 7-segment codes for 0–9 in array

2. Timer2 Multiplexing:
   - Prescaler 32, preload 255-250 ≈ 1 ms overflow
   - Interrupt-driven digit switching (~250 Hz refresh)
   - Displays 4-digit number (LSD to MSD)

3. Input Handling:
   - PB4 as button input with pull-up
   - 50ms debounce, increments counter (0–9999)
   - Resets to 0 at 10000

Connections to Embedded Systems:
1. Hardware Integration:
   - PORTA to 7-segment lines (A–G, DP)
   - PORTB (PB0–PB3) to digit enables
   - PB4 to button (active-low with pull-up)
   - Typical 4-digit display setup

2. Real-Time Operation:
   - ~250 Hz digit refresh (flicker-free)
   - Responsive button input with debounce
   - Suitable for counters or timers

3. Resource Utilization:
   - Uses Timer2, PORTA fully, 5 pins of PORTB
   - Small code size with interrupt handling
   - Efficient multiplexing via ISR

Pros for Embedded Applications:
1. Efficiency:
   - Interrupt-driven display refresh
   - Minimal CPU load in main loop
   - Smooth multiplexing at 250 Hz

2. Reliability:
   - Debounced button input
   - Accurate digit display mapping
   - Robust counter logic

3. Practicality:
   - Simple counter with user input
   - Reusable 7-segment functions
   - Good for numeric displays

Potential Improvements for Embedded Use:
1. Add adjustable refresh rate
2. Implement power-saving modes
3. Add multi-button controls (e.g., reset)
4. Support decimal point usage

Typical Applications:
- Digital counters or timers
- Event counters with button input
- Display modules in appliances
- Educational projects for interrupts/displays