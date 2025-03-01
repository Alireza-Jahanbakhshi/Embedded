SPI_SDCard
----------------------------

Description:
This AVR microcontroller program (designed for an 8 MHz clock) interfaces with an SD card via SPI and provides a UART-based interactive menu for reading, writing, and erasing blocks. It initializes SPI at 125 kHz for SD card setup, then switches to 4 MHz, and uses UART at 19200 baud for user interaction. The code supports single-block read/write (512 bytes) and multi-block erase operations, with status feedback via LED and UART.

Key Features:
1. SPI Configuration:
   - Initial 125 kHz (fosc/128), then 4 MHz (fosc/2 with 2X)
   - SS (PB4), MOSI (PB5), SCK (PB7) outputs; MISO (PB6) input
   - Full-duplex SPI for SD card communication

2. SD Card Operations:
   - Initialization (CMD0, CMD1, CMD16 for 512-byte blocks)
   - Single-block read/write (CMD17, CMD24)
   - Block erase (CMD32, CMD33, CMD38)

3. UART Interface:
   - 19200 baud, 8N1
   - Menu-driven: erase (0), write (1), read (2)
   - Interactive block selection and data input/output

Connections to Embedded Systems:
1. Hardware Integration:
   - SPI: PB4 (SS), PB5 (MOSI), PB6 (MISO), PB7 (SCK) to SD card
   - UART: PD0 (RXD), PD1 (TXD) to terminal/PC; PD2 (LED) for status
   - SD card requires 3.3V power and level shifting if needed

2. Real-Time Operation:
   - Interactive command processing
   - Fast SPI (4 MHz) after initialization
   - Suitable for file system prototyping

3. Resource Utilization:
   - Uses SPI and UART modules, 7 I/O pins
   - 512-byte buffer in RAM
   - Polling-based, no interrupts

Pros for Embedded Applications:
1. Functionality:
   - Comprehensive SD card operations
   - User-friendly UART interface
   - Robust initialization and error checking

2. Debug Support:
   - Detailed UART feedback
   - LED status indicator
   - Easy to monitor operations

3. Versatility:
   - Supports multiple block operations
   - Extensible for file system integration
   - Good for SD card prototyping

Potential Improvements for Embedded Use:
1. Add interrupt-driven UART/SPI
2. Implement multi-block read/write
3. Add file system support (e.g., FAT16)
4. Include power-saving modes

Typical Applications:
- Data storage/logging systems
- SD card testing and development
- Embedded file systems
- Educational projects for SPI/SD/UART