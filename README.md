# STM32 Google Dino Automation

## Project Objective
To develop an autonomous system using the STM32F411CEU6 that detects obstacles in the Google Chrome Dino game and performs timely jumps and ducks using sensor feedback and servo motor control.

## Components and Their Purpose

- **STM32F411CEU6 Black Pill:** Main microcontroller responsible for sensor processing, timing, decision-making, and peripheral control.
- **GL5528 Photoresistors (3):** Detect approaching cacti and flying birds by sensing changes in screen brightness.
- **10 kΩ Resistors (3):** Form voltage dividers with the photoresistors to provide measurable analog voltages to the STM32 ADC.
- **SG90 Servo Motors (2):** Physically press the keyboard's spacebar for jumping and down arrow for ducking.
- **Breadboard Power Module:** Powers the servos separately from the microcontroller.
- **470 µF Capacitor:** Helps stabilize the servo power supply during current surges.
- **SSD1306 OLED Display (0.96"):** Displays operating mode and game statistics.
- **microSD Card Module:** Stores game logs and the best score.
- **Push Button:** Starts a new round.

## Features

- Automatic obstacle detection and classification.
- Timed jumping and ducking.
- ADC with DMA for continuous sensor acquisition.
- Timer-based obstacle speed measurement and action scheduling.
- Automatic sensor calibration.
- Game over detection and logging of every round to SD card.
- UART communication with an external guitar-detection board.
- Watchdog that restarts the system if it freezes.

## Communication and Peripherals

- **ADC + DMA:** Photoresistor readings.
- **PWM (TIM4):** Servo motor control.
- **I2C1:** OLED display communication.
- **SPI1:** microSD card communication.
- **USART1:** Communication with the guitar board.
- **GPIO / EXTI:** Button input and LED control.
- **TIM2 / TIM5:** ADC triggering, timing, and event scheduling.
- **IWDG:** Watchdog.

## Development

- STM32CubeIDE
- STM32 HAL Library
- C programming language

## Progress

| Part | What | Peripherals | Status |
|---|---|---|---|
| 1 | LED and button | GPIO, EXTI | Done |
| 2 | Jump and duck servos | TIM4 PWM | Done (need tuning on keyboard) |
| 3 | OLED screen with mode and counters | I2C1 | Done |
| 4 | Connection with guitar board | USART1 | Done (tested with Arduino) |
| 5 | Watchdog | IWDG | Done |
| 6 | Reading photoresistors | ADC, DMA, TIM2 | Next |
| 7 | Detecting obstacles and jumping | - | Planned |
| 8 | START button and game over detection | GPIO, EXTI | Planned |
| 9 | Logging games to SD card | SPI1 | Planned |

**Part 1:** Onboard LED (PC13) is blinking slow in Auto mode and fast in Guitar mode. KEY button (PA0) changes the mode with interrupt, presses closer than 200 ms are ignored because of bouncing.

**Part 2:** Two servos with PWM from TIM4, PB8 for jump and PB9 for duck. Prescaler 99 and period 19999 gives 50 Hz, so CCR value is the pulse width in us. Servo goes to press position and after 200 ms (jump) or 300 ms (duck) comes back. For testing, in Auto mode servos are pressing one after another every 500 ms. Servos are powered from separate breadboard power module, not from the board.

**Part 3:** OLED screen 0.96" (SSD1306) on I2C1, PB6 and PB7. It shows the mode and the number of jumps and ducks. Screen is updated only when something changes, because sending the full picture takes some time. Every time the mode changes, counters are reset to 0. For the screen I used the stm32-ssd1306 library.

**Part 4:** USART1 on PA10 (RX), 115200 baud. Guitar board sends one letter: 'H' (high note) = jump, 'L' (low note) = duck. Commands work only in Guitar mode. Receiving is done with interrupt, and if some error happens on the line, receiving starts again automatically. I tested it with Arduino Mega (Serial1, pin 18 -> PA10).

**Part 5:** Watchdog (IWDG) with about 1 second timeout. Main loop refreshes it every time, so if the program freezes, the board restarts by itself. While debugging, the watchdog is paused.

Note: board must be powered from USB-C or from ST-Link 3.3V. Servo power module ground must be connected to board ground. On long breadboards the power lines are split in the middle, they need to be connected with wires.

**Course:** ENGS 251 – Embedded Systems Project
