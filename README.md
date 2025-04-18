# Embedded MCU Firmware Repository

## Overview

This repository provides **firmware examples and templates** for embedded development using various **microcontrollers (MCUs)**. The initial release is focused on the **AVR ATmega16A** microcontroller from **Microchip Technology (Atmel)**, but support for additional MCUs will be added in future updates.

This repository serves as a **comprehensive reference** for developers, students, and embedded system enthusiasts, offering **ready-to-use code examples** for various peripherals to accelerate development and learning.

## Features

✅ Peripheral driver examples for **AVR ATmega16A**  
✅ Organized directory structure for easy navigation  
✅ Compatible with **GCC for AVR, Atmel Studio, and Microchip MPLAB X IDE**  
✅ Planned support for **STM32, ESP32, PIC, and ARM Cortex-M**  
✅ Open-source under the **MIT License**

## 📚 New Content: C Programming Tutorial

We've added a comprehensive **C Programming Tutorial** to help beginners and intermediate developers master the language. This tutorial includes:

- Core concepts of C (variables, data types, operators, control structures)
- Functions, pointers, and memory management
- File handling and standard libraries
- Modular programming with **library creation**
- All examples formatted using **K&R (Kernighan and Ritchie) style**

👉 Check out `C.md` for the full tutorial!

## Repository Structure

```
Embedded/
├── C.md                                # 📘 C Programming Tutorial (with K&R style)
└── MicrochipTechnology/
    └── AVR_FW_ATmega_V1.0.0/
        └── ATmega16APU_DevBoard/
            ├── Examples/               # Peripheral driver examples
            │   ├── ADC/                # Analog-to-Digital Converter
            │   ├── EXTI/               # External Interrupts
            │   ├── GPIO/               # General Purpose I/O
            │   ├── I2C/                # Inter-Integrated Circuit
            │   ├── RTC/                # Real-Time Clock
            │   ├── SPI/                # Serial Peripheral Interface
            │   ├── TIM/                # Timers
            │   ├── UART/               # Serial Communication (UART)
            │   └── WDT/                # Watchdog Timer
            └── Templates/
                └── Project/           # Project base template

```

Each peripheral directory contains **multiple subdirectories** for different firmware implementations, typically with a `Debug` folder containing compiled/debugging outputs.

## Getting Started

### Prerequisites

Before using this repository, ensure you have the following:

- **AVR Toolchain** (GCC for AVR, AVRDUDE, etc.)
- **Atmel Studio / Microchip MPLAB X IDE** (optional but recommended)
- **AVR Programmer** (e.g., USBasp, AVRISP mkII, etc.)
- **ATmega16A Development Board** (or other AVR-based hardware)

### Installation & Usage

#### 1️⃣ Clone the Repository

```sh
git clone https://github.com/yourusername/Embedded-MCU-FW.git
cd Embedded-MCU-FW
```

#### 2️⃣ Compile the Firmware

Use the **AVR toolchain** to compile the firmware.

```sh
avr-gcc -mmcu=atmega16 -o main.elf main.c
avr-objcopy -O ihex main.elf main.hex
```

#### 3️⃣ Flash the Firmware

Upload the compiled firmware to the **ATmega16A** using **AVRDUDE**:

```sh
avrdude -c usbasp -p m16 -U flash:w:main.hex:i
```

## Future Plans 🛠️

🔹 Expand support for **other MCUs** (STM32, ESP32, PIC, ARM Cortex-M)  
🔹 Add more **RTOS**, **low-power mode**, and **communication protocol** examples  
🔹 Provide **comprehensive documentation** and step-by-step **tutorials**

## Contributing 🤝

We welcome contributions! If you’d like to **add support for another MCU** or **enhance existing examples**, feel free to **submit a pull request**. Let’s build a **powerful embedded development resource together!** 🚀

## License 📜

This project is licensed under the **MIT License**. See `LICENSE` for more details.

**Let’s innovate and build better embedded systems! 🚀**
