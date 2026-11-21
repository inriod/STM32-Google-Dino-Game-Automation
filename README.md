# STM32 Google Dino Automation

## Project Objective
To develop an autonomous system using the STM32F411CEU6 that detects obstacles in the Google Chrome Dino game and performs timely jumps and ducks using sensor feedback and servo motor control.

## Components and Their Purpose

- **STM32F411CEU6 Black Pill:** Main microcontroller responsible for sensor processing, timing, decision-making, and peripheral control.
- **GL5528 Photoresistors (2):** Detect approaching cacti (ground level) and flying birds (head level) by sensing changes in screen brightness.
- **10 kΩ Resistors (2):** Form voltage dividers with the photoresistors to provide measurable analog voltages to the STM32 ADC.
- **SG90 Servo Motors (2):** Physically press the keyboard's spacebar for jumping and down arrow for ducking.
- **Breadboard Power Module:** Powers the servos and the Bluetooth module separately from the microcontroller.
- **470 µF Capacitor:** Helps stabilize the servo power supply during current surges.
- **SSD1306 OLED Display (0.96"):** Displays operating mode and game statistics.
- **HC-05 Bluetooth Modules (2):** Wireless UART link between the STM32 and the guitar board.
- **microSD Card Module (planned):** Stores game logs.
- **Push Button:** Starts and stops a round.

## Features

- Automatic obstacle detection and classification (cacti and birds).
- Jumping over cacti and ducking under birds.
- ADC with DMA for continuous sensor acquisition.
- Automatic sensor calibration at the start of every round.
- Game over detection.
- Wireless UART communication with an external guitar-detection board over Bluetooth.
- Watchdog that restarts the system if it freezes.
- Logging of every round to SD card (planned).

## Communication and Peripherals

- **ADC + DMA:** Photoresistor readings (PA1, PB0).
- **TIM2:** ADC triggering, 10,000 times per second.
- **PWM (TIM4):** Servo motor control.
- **I2C1:** OLED display communication.
- **USART1:** Bluetooth communication with the guitar board (9600 baud).
- **SPI1:** microSD card communication (planned).
- **GPIO / EXTI:** Button input and LED control.
- **IWDG:** Watchdog.

## Development

- STM32CubeIDE
- STM32 HAL Library
- C programming language

## Progress

| Part | What | Peripherals | Status |
|---|---|---|---|
| 1 | LED and button | GPIO, EXTI | Done |
| 2 | Jump and duck servos | TIM4 PWM | Done |
| 3 | OLED screen with mode and counters | I2C1 | Done |
| 4 | Bluetooth connection with guitar board | USART1 | Done (tested with Arduino Mega) |
| 5 | Watchdog | IWDG | Done |
| 6 | Reading photoresistors | ADC, DMA, TIM2 | Done |
| 7 | Detecting cacti and jumping | - | Done |
| 8 | START button and auto calibration | GPIO, EXTI | Done |
| 9 | Detecting birds and ducking | - | Done |
| 10 | Game over detection | - | Done |
| 11 | Logging games to SD card | SPI1 | Next |

**Part 1:** Onboard LED (PC13) is blinking slow in Auto mode and fast in Guitar mode. KEY button (PA0) changes the mode with interrupt, presses closer than 200 ms are ignored because of bouncing.

**Part 2:** Two servos with PWM from TIM4, PB8 for jump and PB9 for duck. Prescaler 99 and period 19999 gives 50 Hz, so CCR value is the pulse width in us. Servo goes to press position and after some time comes back (200 ms for jump, 800 ms for duck in Auto mode). Servos are powered from separate breadboard power module, not from the board.

**Part 3:** OLED screen 0.96" (SSD1306) on I2C1, PB6 and PB7. It shows the mode (or PRESS START) and the number of jumps and ducks. Screen is updated only when something changes, because sending the full picture takes some time. Counters are reset when the mode changes and when a new round starts. For the screen I used the stm32-ssd1306 library.

**Part 4:** USART1 on PA9/PA10 is connected to HC-05 Bluetooth module, 9600 baud. Guitar board sends one letter: 'H' (high note) = jump, 'L' (low note) = duck. Commands work only in Guitar mode. Receiving is done with interrupt, and if some error happens on the line, receiving starts again automatically. I tested it with second HC-05 on Arduino Mega. One module is set as master and other as slave with AT commands, so they connect by themselves.

**Part 5:** Watchdog (IWDG) with about 1 second timeout. Main loop refreshes it every time, so if the program freezes, the board restarts by itself. While debugging, the watchdog is paused.

**Part 6:** Two photoresistors with 10 kΩ resistors as voltage divider, on PA1 (LDR A, ground level) and PB0 (LDR C, head level). TIM2 triggers the ADC 10,000 times per second and DMA puts the values in an array, so the CPU does not need to read them.

**Part 7:** LDR A is in front of the dino. When cactus comes, the screen gets darker, value goes below the threshold and the servo presses space. After the cactus passes, value must go clearly above the threshold again before next jump, so one cactus gives only one jump.

**Part 8:** START button on PB12. When pressed, the board presses space to start the game, measures the empty screen brightness, and sets the threshold 250 below it. So it works even if room light or monitor brightness changes. Pressing START again stops the round.

**Part 9:** LDR C is placed little higher than the dino head. If LDR C sees something dark but LDR A sees nothing, it is a bird, so the duck servo holds down arrow until the bird passes. If both are dark, it is a tall cactus, so the dino jumps.

**Part 10:** If both LDRs see nothing for 5 seconds, the game is over (after crash the picture stops moving), and the screen goes back to PRESS START.

Note: board is powered from ST-Link 3.3V (or USB-C). Servos and Bluetooth module are powered from the power module, and power module ground must be connected to board ground. On long breadboards the power lines are split in the middle, they need to be connected with wires.

## About game speed

The game becomes faster with time. I tried to calculate the speed with formula from the game source code, but the game rounds the movement every frame and it depends on monitor refresh rate, so the timing was not exact. For the demo the game speed is fixed from browser console (speed 9, so birds also appear):

```js
r = Runner.getInstance(); r.config.acceleration = 0; r.config.speed = 9; r.currentSpeed = 9
```

**Course:** ENGS 251 – Embedded Systems Project
