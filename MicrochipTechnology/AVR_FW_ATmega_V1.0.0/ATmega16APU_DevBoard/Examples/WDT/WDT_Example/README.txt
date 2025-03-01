WDT_Example
----------------------------

Description:
This AVR microcontroller program (designed for an 8 MHz clock) demonstrates the use of the Watchdog Timer (WDT) with a 2-second timeout. It configures PB0 as an output to toggle an LED every 500ms and resets the WDT in each loop iteration to prevent a system reset. The code showcases basic WDT functionality for ensuring system reliability.

Key Features:
1. WDT Configuration:
   - 2-second timeout (WDP2:WDP1:WDP0 = 110)
   - Enabled via WDTCR register
   - Reset function to "kick" the watchdog

2. GPIO Demonstration:
   - PB0 as output for LED toggling
   - 500ms toggle period (well below WDT timeout)
   - Simple visual feedback

3. Operation Logic:
   - Infinite loop with periodic WDT resets
   - Ensures system stays alive
   - Blocking delay implementation

Connections to Embedded Systems:
1. Hardware Integration:
   - PB0 connects to an LED (with current-limiting resistor)
   - Minimal pin usage for demonstration
   - WDT uses internal AVR hardware

2. Real-Time Operation:
   - Periodic 500ms LED toggle
   - WDT reset within 2-second window
   - Suitable for reliability monitoring

3. Resource Utilization:
   - Uses one GPIO pin (PB0)
   - Minimal code size with WDT control
   - No interrupts beyond WDT reset

Pros for Embedded Applications:
1. Reliability:
   - Prevents system hang with 2s timeout
   - Simple reset mechanism
   - Ensures continuous operation

2. Simplicity:
   - Easy to implement and test
   - Clear WDT usage example
   - Minimal resource requirements

3. Safety:
   - WDT protects against infinite loops
   - LED toggle confirms operation
   - Good for critical systems

Potential Improvements for Embedded Use:
1. Add error handling or recovery logic
2. Use interrupts for LED toggling
3. Implement configurable timeout
4. Add WDT disable option for debugging

Typical Applications:
- System reliability monitoring
- Watchdog for critical embedded systems
- Basic fault detection
- Educational projects for WDT usage