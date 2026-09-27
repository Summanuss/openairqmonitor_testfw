# Open AirQ Monitor — Test Firmware

![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)
![Status](https://img.shields.io/badge/status-stable-green.svg)


## Table of Contents
- [Overview](#overview)
- [Related Hardware](#related-hardware)
- [Requirements](#requirements)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Building](#building)
- [Flashing](#flashing)
- [Usage](#usage)
- [Configuration](#configuration)
- [License](#license)
- [Contact](#contact)


## Overview
This repository contains the test firmware for the **Open AirQ Monitor** custom STM32-based board.<br>
The bring-up firmware is written in C and targets the STM32L431CCT6TR microcontroller.


## Related Hardware
This firmware is designed to run on the Open VOC Monitor PCB (Revision 2.0).
- **Hardware repository:** [Board Repo](https://github.com/Summanuss/openairqmonitor.git)


## Requirements

### Hardware
- SWD programmer (e.g. ST-Link V2)
- USB to TTL converter
- USB-C cable (5V power)

### Software / Toolchain
  - **STM32CubeIDE:** v2.2.0 or later
  - **STM32CubeMX:** Firmware is (partially) auto generated from a CubeMX configuration
  - `arm-none-eabi-gcc` (GNU Tools for STM32 14.3 rel 1)
  - **STM32CubeProgrammer:** To inspect, flash and erase memory (optional)
  - **STM32L4 HAL/LL drivers:** Version 1.18.2


## Project Structure
```text
├── Core/                   # Sources and headers
├── Drivers/                # HAL/LL and CMSIS drivers
├── st7735_lib/             # ST7735S library
├── .cproject               # CubeIDE project
├── .project                # CubeIDE project
├── STM32L431CCT6TR.ioc     # CubeMX config project
├── STM32L431CCTX_FLASH.ld  # Linker script
├── .gitignore              # GitIgnore file
├── LICENSE.md       
└── README.md         
```


## Getting Started
1. Clone this repository:
   ```
   git clone https://github.com/Summanuss/openairqmonitor_testfw.git
   ```
2. Open the project in **STM32CubeIDE**.
3. Power up the device via USB-C.
4. Connect the ST-LINK to `SWDIO` and `SWCLK` pins - see hardware repo pinout.
5. Connect the converter to `USART_RX` and `USART_TX` pins - see hardware repo pinout


## Building
Use the default `Debug` configuration.


## Flashing
Use the provided .launch file in the repository. <br>
Alternatively, flash via **STM32CubeProgrammer** the generated .elf file after build.


## Usage
Via your favourite serial terminal (I used RealTerm) open up a COM with correct settings and inspect the output.<br>
Alternatively, setup a debug session with STM32CubeIDE and inspect the execution that way.


## Configuration
Tests can be enable / disabled by settings the provided `#define` in **tests_config.h**.


## License
Distributed under the Apache-2.0 License. See `LICENSE` for more information.


## Contact
Mail: serafin.jacopo99@gmail.com