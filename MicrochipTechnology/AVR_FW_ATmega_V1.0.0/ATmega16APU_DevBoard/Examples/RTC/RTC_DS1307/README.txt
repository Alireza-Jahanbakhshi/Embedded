RTC_DS1307
----------------------------

Description:
This AVR microcontroller program (designed for an 8 MHz clock) interfaces with a DS1307 real-time clock (RTC) over I2C and outputs the time and date via UART at 9600 baud. It initializes the RTC, sets an initial time (optional), and continuously reads and displays the time (HH:MM:SS) and date (DD/MM/YY) in BCD format every second. The I2C operates at 50 kHz, and UART uses a printf-style output.

Key Features:
1. I2C Configuration:
   - 50 kHz clock frequency (TWBR=72 at 8 MHz)
   - DS1307 address: 0xD0 (write), 0xD1 (read)
   - Functions for start, stop, read, and write

2. RTC Functionality:
   - Structure for time/date (sec, min, hour, week_day, date, month, year)
   - Sets and reads BCD-formatted values
   - Disables DS1307 square wave output

3. UART Output:
   - 9600 baud, 8N1 configuration
   - printf-style output redirected to UART
   - Displays time and date every second

Connections to Embedded Systems:
1. Hardware Integration:
   - SDA (PC1) and SCL (PC0) to DS1307 I2C pins
   - UART TX (PD1) to serial terminal/PC
   - DS1307 requires 32.768 kHz crystal and backup battery

2. Real-Time Operation:
   - Accurate timekeeping via DS1307
   - 1-second update rate via delay
   - Suitable for logging or monitoring

3. Resource Utilization:
   - Uses TWI module and UART hardware
   - Moderate memory due to printf usage
   - No interrupts, polling-based

Pros for Embedded Applications:
1. Accuracy:
   - Leverages DS1307’s precise RTC
   - Consistent 1-second updates
   - Reliable BCD timekeeping

2. Debug Support:
   - UART output for easy monitoring
   - Formatted time/date display
   - Useful for development and testing

3. Modularity:
   - Reusable I2C and RTC functions
   - Extensible for additional DS1307 features
   - Good base for RTC projects

Potential Improvements for Embedded Use:
1. Add error checking for I2C transactions
2. Implement interrupt-driven UART/I2C
3. Replace printf with custom formatting
4. Add time-setting interface (e.g., buttons)

Typical Applications:
- Timekeeping in embedded systems
- Data logging with timestamps
- Clock displays with serial output
- Educational projects for RTC/I2C/UART