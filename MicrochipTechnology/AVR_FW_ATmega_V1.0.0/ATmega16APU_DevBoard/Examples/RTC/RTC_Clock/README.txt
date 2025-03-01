RTC_Clock
----------------------------

Description:
This AVR microcontroller program (designed for an 8 MHz clock) implements a real-time clock (RTC) displayed on a 4-digit 7-segment display. It uses Timer2 with a 32.768 kHz crystal for 1-second interrupts to track time (hours, minutes, seconds) and Timer0 for multiplexing the display at approximately 488 Hz (2.048 ms period). The display shows minutes and seconds in an SS.MM format due to reversed segment mapping.

Key Features:
1. Display Configuration:
   - 7-segment pins on PORTA (PA0-PA7: A-G, DP)
   - Digit selection on PORTB (PB0-PB3: Segment3-Segment0)
   - Common-anode display assumed (low = on)

2. Timekeeping:
   - Timer2: 1-second interrupts (32.768 kHz / 128)
   - Tracks hours (0-23), minutes (0-59), seconds (0-59)
   - Display shows MMSS value, mapped as SS.MM

3. Multiplexing:
   - Timer0: ~488 Hz refresh (8 MHz / 64 / 256)
   - Updates one digit every 2 interrupts (244 Hz per digit)
   - Decimal point toggled for seconds/minutes separation

Connections to Embedded Systems:
1. Hardware Integration:
   - PORTA to 7-segment lines (A-G, DP)
   - PORTB (PB0-PB3) to digit enables (Segment3-Segment0)
   - TOSC1 pin to 32.768 kHz crystal for Timer2
   - Typical RTC display setup

2. Real-Time Operation:
   - Accurate 1-second timekeeping via Timer2
   - Smooth multiplexing for flicker-free display
   - Continuous time update in main loop

3. Resource Utilization:
   - Uses PORTA fully, 4 pins of PORTB
   - Two timers (Timer0, Timer2)
   - Interrupt-driven for efficiency

Pros for Embedded Applications:
1. Accuracy:
   - Crystal-based 1-second timing
   - Reliable multiplexing for clear display
   - Robust timekeeping logic

2. Efficiency:
   - Interrupt-driven display and timing
   - Minimal CPU load in main loop
   - Optimized for low-power RTC tasks

3. Practicality:
   - Compact 4-digit time display
   - SS.MM format with decimal point
   - Good for clock or timer applications

Potential Improvements for Embedded Use:
1. Add time setting via buttons
2. Correct SS.MM to MM:SS display order
3. Implement power-saving sleep modes
4. Add alarm functionality

Typical Applications:
- Digital clocks or timers
- Time displays in appliances
- Embedded RTC modules
- Educational projects for timers/displays