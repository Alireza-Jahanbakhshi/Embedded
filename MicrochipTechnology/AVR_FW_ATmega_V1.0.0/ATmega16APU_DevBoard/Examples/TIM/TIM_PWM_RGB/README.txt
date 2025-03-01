TIM_PWM_RGB
----------------------------

Description:
This AVR microcontroller program (designed for an 8 MHz clock) uses PWM to control an RGB LED with three channels: Red (PD5/OC1A), Green (PD4/OC1B), and Blue (PB3/OC0). It configures Timer1 (8-bit Fast PWM) for Red and Green, and Timer0 (Fast PWM) for Blue, both with a prescaler of 8 (~3.9 kHz frequency). The code cycles through solid colors (Red, Green, Blue, White, Off) with 1-second delays.

Key Features:
1. PWM Configuration:
   - Timer0: PB3 (OC0) for Blue, Fast PWM, prescaler 8
   - Timer1: PD5 (OC1A) for Red, PD4 (OC1B) for Green, 8-bit Fast PWM, prescaler 8
   - Frequency: 8 MHz / 8 / 256 = ~3.9 kHz

2. RGB Control:
   - 0-255 intensity range per channel
   - Non-inverted PWM mode
   - Simple function to set all three colors

3. Operation Sequence:
   - Cycles: Red, Green, Blue, White, Off
   - 1-second duration per state (5-second full cycle)
   - Blocking delay implementation

Connections to Embedded Systems:
1. Hardware Integration:
   - Red (PD5), Green (PD4), Blue (PB3) to RGB LED pins
   - Common anode/cathode LED with current-limiting resistors
   - Typical setup for RGB lighting control

2. Real-Time Operation:
   - Smooth PWM-driven color changes
   - Fixed 1-second timing per color
   - Suitable for visual effects or indicators

3. Resource Utilization:
   - Uses Timer0, Timer1, and 3 I/O pins
   - Minimal code size with simple logic
   - No interrupts, polling-based

Pros for Embedded Applications:
1. Precision:
   - Accurate 8-bit PWM control per channel
   - Consistent 3.9 kHz frequency
   - Reliable color sequencing

2. Simplicity:
   - Easy to configure and test
   - Clear RGB PWM example
   - Minimal hardware requirements

3. Versatility:
   - Adjustable color values
   - Extensible for fading or patterns
   - Good base for RGB projects

Potential Improvements for Embedded Use:
1. Add color fading transitions
2. Use interrupts for timing
3. Implement dynamic color input
4. Add power-saving modes

Typical Applications:
- RGB LED status indicators
- Decorative lighting effects
- Mood lighting controls
- Educational projects for PWM/RGB