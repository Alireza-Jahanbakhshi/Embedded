GPIO_InfraredOnLCD
----------------------------

Description:
This AVR microcontroller program (designed for an 8 MHz clock) implements an infrared (IR) detection counter with a 16x2 LCD display in 4-bit mode. It uses PB0 to read an IR sensor (assumed active-low output from an LM358N op-amp) and displays the detection count on the LCD. The code includes basic debouncing and updates the display each time an IR beam is interrupted.

Key Features:
1. GPIO Configuration:
   - PB0 as input with pull-up for IR sensor
   - PORTD pins (PD2-PD7) as outputs for LCD in 4-bit mode

2. IR Detection:
   - Polling-based detection on PB0
   - 20ms debounce delay for stability
   - Counts rising edges (release after detection)

3. LCD Display:
   - 4-bit mode interface (D4-D7 on PD4-PD7, RS on PD2, EN on PD3)
   - Displays static "IR Detections:" on line 1
   - Updates "Count: XX" on line 2 with detection count

Connections to Embedded Systems:
1. Hardware Integration:
   - IR sensor output (e.g., from LM358N) to PB0
   - LCD connected to PORTD (PD2-PD7)
   - Typical setup for counting objects or detecting interruptions

2. Real-Time Operation:
   - Continuous polling of IR sensor state
   - Immediate display updates on detection
   - Simple event-driven application

3. Resource Utilization:
   - Uses one input pin and six output pins
   - Small memory footprint despite sprintf usage
   - No interrupts, keeping CPU fully available

Pros for Embedded Applications:
1. Functionality:
   - Effective for counting IR beam breaks
   - Clear visual feedback via LCD
   - Simple yet practical application

2. Reliability:
   - Debouncing reduces false triggers
   - Pull-up on input ensures stable state
   - Robust polling loop for continuous monitoring

3. Adaptability:
   - Easily adjustable for different IR sensors
   - LCD functions reusable for other displays
   - Counter logic extensible to other inputs

Potential Improvements for Embedded Use:
1. Replace sprintf with custom int-to-string function
2. Add interrupt-driven IR detection
3. Implement power-saving sleep modes
4. Add reset functionality for counter

Typical Applications:
- Object counting on conveyor belts
- Intrusion detection systems
- Traffic monitoring (beam break)
- Educational projects for IR and LCD interfacing