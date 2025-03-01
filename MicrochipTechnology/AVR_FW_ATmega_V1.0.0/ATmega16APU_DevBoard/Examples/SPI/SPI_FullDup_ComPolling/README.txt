SPI_FullDup_ComPolling
----------------------------

Description:
This AVR microcontroller program (designed for an 8 MHz clock) demonstrates full-duplex SPI communication using polling. It supports both master and slave configurations on an ATmega16, utilizing PORTB pins (PB4-PB7) for SPI signals. The master sends a byte (0x55) every 100ms and receives data simultaneously, while the slave section (commented out) provides a framework for receiving data. The SPI clock rate is set to fck/16 (500 kHz at 8 MHz).

Key Features:
1. SPI Configuration:
   - Master: MOSI (PB5), SCK (PB7), SS (PB4) outputs; MISO (PB6) input
   - Slave: MISO output; MOSI, SCK, SS inputs
   - 500 kHz clock (fck/16)

2. Master Operation:
   - Transmits 0x55 and receives data in full-duplex mode
   - 100ms delay between transmissions
   - SS pin controlled manually

3. Slave Framework:
   - Commented section for slave reception
   - Polling-based data retrieval
   - Easily enabled on a second device

Connections to Embedded Systems:
1. Hardware Integration:
   - Master/Slave SPI pins: SS (PB4), MOSI (PB5), MISO (PB6), SCK (PB7)
   - Connects master to slave via 4-wire SPI bus
   - Typical setup for peripheral communication

2. Real-Time Operation:
   - Periodic 100ms data exchange (master)
   - Synchronous full-duplex communication
   - Suitable for data transfer between devices

3. Resource Utilization:
   - Uses SPI hardware module and 4 PORTB pins
   - Minimal code size with basic functions
   - Polling-based, no interrupts

Pros for Embedded Applications:
1. Simplicity:
   - Easy to configure as master or slave
   - Clear full-duplex SPI example
   - Minimal setup requirements

2. Versatility:
   - Supports both master and slave modes
   - Data byte (0x55) easily modifiable
   - Good for prototyping SPI communication

3. Reliability:
   - Fixed 100ms transmission interval (master)
   - Standard SPI protocol implementation
   - Robust polling for small-scale use

Potential Improvements for Embedded Use:
1. Add error checking for SPI status
2. Implement interrupt-driven SPI
3. Add slave transmit capability
4. Include SS pin automation for multi-slave

Typical Applications:
- Inter-device data exchange
- SPI peripheral communication (e.g., sensors, displays)
- Master-slave control systems
- Educational projects for SPI basics