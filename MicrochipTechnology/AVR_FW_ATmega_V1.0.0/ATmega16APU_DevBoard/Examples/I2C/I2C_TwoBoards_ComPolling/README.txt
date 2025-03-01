I2C_TwoBoards_ComPolling
----------------------------

Description:
This AVR microcontroller program (designed for an 8 MHz clock) demonstrates I2C (TWI) communication between two boards using polling. The master section continuously sends a byte (0x55) to a slave at address 0x20 every 100ms. The slave section (commented out) provides a basic framework for receiving data. The code configures the TWI module for 100 kHz operation and includes standard I2C functions for start, stop, write, and read operations.

Key Features:
1. I2C/TWI Configuration:
   - 100 kHz clock frequency (TWBR=32 at 8 MHz)
   - Master sends data to slave address 0x20
   - SDA on PC1, SCL on PC0 (ATmega16 pinout)

2. Master Operation:
   - Sends 0x55 repeatedly in an infinite loop
   - 100ms delay between transmissions
   - Polling-based control of TWI

3. Slave Framework:
   - Commented section for slave polling
   - Basic data reception structure
   - Easily enabled on a second board

Connections to Embedded Systems:
1. Hardware Integration:
   - SDA (PC1) and SCL (PC0) connect between master and slave
   - Slave board requires pull-up resistors (typically 4.7kΩ)
   - Common setup for inter-board communication

2. Real-Time Operation:
   - Periodic data transmission every 100ms
   - Polling ensures synchronous operation
   - Suitable for simple data exchange

3. Resource Utilization:
   - Uses TWI hardware module
   - Minimal code size with basic functions
   - No interrupts, relying on polling

Pros for Embedded Applications:
1. Simplicity:
   - Easy to implement and test
   - Clear master-slave communication example
   - Minimal setup for I2C basics

2. Reliability:
   - Fixed 100ms transmission interval
   - Standard I2C protocol implementation
   - Robust polling for small-scale use

3. Flexibility:
   - Slave address adjustable (0x20)
   - Data byte (0x55) easily modified
   - Extensible for multi-byte communication

Potential Improvements for Embedded Use:
1. Add error checking for TWI status
2. Implement interrupt-driven I2C
3. Add slave response mechanism
4. Include power-saving modes

Typical Applications:
- Inter-board data sharing
- Sensor data polling between devices
- Master-slave control systems
- Educational projects for I2C communication