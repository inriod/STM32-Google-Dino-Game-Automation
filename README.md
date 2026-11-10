# STM32 Google Dino Automation

## Project Objective
To develop an autonomous system using the STM32F411CEU6 that detects obstacles in the Google Chrome Dino game and performs timely jumps and ducks using sensor feedback and servo motor control.

## Components and Their Purpose

- **STM32F411CEU6 Black Pill:** Main microcontroller responsible for sensor processing, timing, decision-making, and peripheral control.
- **GL5528 Photoresistors (3):** Detect approaching cacti and flying birds by sensing changes in screen brightness.
- **10 kΩ Resistors (3):** Form voltage dividers with the photoresistors to provide measurable analog voltages to the STM32 ADC.
- **SG90 Servo Motors (2):** Physically press the keyboard's spacebar for jumping and down arrow for ducking.
- **470 µF Capacitor:** Helps stabilize the servo power supply during current surges.
- **ST7735 TFT Display:** Displays system information, operating mode, and game statistics.
- **AT24C32 EEPROM:** Stores sensor calibration settings and the best score.
- **USB-UART Adapter:** Provides serial communication between the STM32 and a PC for debugging and commands.

## Features

- Automatic obstacle detection and classification.
- Timed jumping and ducking.
- ADC with DMA for continuous sensor acquisition.
- Timer-based obstacle speed measurement and action scheduling.
- Automatic sensor calibration.
- UART communication with a PC and an external guitar-detection board.

## Communication and Peripherals

- **ADC + DMA:** Photoresistor readings.
- **PWM (TIM4):** Servo motor control.
- **SPI1:** TFT display communication.
- **I2C1:** EEPROM communication.
- **USART1:** Communication with an external board.
- **USART2:** PC communication.
- **GPIO / EXTI:** Button input and LED control.
- **TIM2 / TIM5:** ADC triggering, timing, and event scheduling.

## Development

- STM32CubeIDE
- STM32 HAL Library
- C programming language

**Course:** ENGS 251 – Embedded Systems Project
