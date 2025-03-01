GPIO_RGB
----------------------------

Description:
This AVR microcontroller program (designed for an 8 MHz clock) demonstrates GPIO control to cycle through states of an RGB LED connected to PB0, PB1, and PB2 (PORTB). The code configures these three pins as outputs and uses a counter to increment through binary states (0b000 to 0b110, i.e., 0 to 6), updating every 500ms, effectively cycling through different color combinations before resetting.

Key Features:
1. GPIO Configuration:
   - PB0-PB2 set as outputs for RGB LED control
   - Other PORTB pins remain inputs
   - Direct register manipulation

2. State Cycling:
   - Counter increments from 0 to 6 (0b000 to 0b110)
   - Resets to 0 after reaching 6
   - 500ms delay between states (2-second full cycle)

3. Simple Logic:
   - Linear progression through states
   - No complex timing or interrupts
   - Blocking delay implementation

Connections to Embedded Systems:
1. Hardware Integration:
   - PB0, PB1, PB2 connect to RGB LED (Red, Green, Blue, with current-limiting resistors)
   - Assumes common-anode/common-cathode LED (active-high/active-low adjustable)
   - Minimal pin usage for visual output

2. Real-Time Operation:
   - Consistent 500ms state changes
   - Predictable color cycling pattern
   - Suitable for visual indication or effects

3. Resource Utilization:
   - Uses only 3 GPIO pins
   - Minimal code size with single variable
   - No additional hardware resources needed

Pros for Embedded Applications:
1. Simplicity:
   - Easy to implement and understand
   - Clear demonstration of RGB control
   - Minimal resource requirements

2. Visual Appeal:
   - Cycles through 7 states (off + 6 color combos)
   - Useful for status or decorative purposes
   - Reliable 500ms timing

3. Adaptability:
   - Easily adjustable delay for speed
   - Modifiable for different state sequences
   - Good base for RGB experiments

Potential Improvements for Embedded Use:
1. Add PWM for brightness control
2. Use timers for non-blocking operation
3. Implement color fading transitions
4. Add input to pause or change patterns

Typical Applications:
- RGB LED status indicators
- Decorative lighting effects
- Educational projects for GPIO output
- Simple visual feedback systems