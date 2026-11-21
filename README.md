# STM32 Google Dino Automation

An STM32F411CEU6 Black Pill that plays the Chrome Dino game by itself. Photoresistors on the screen detect obstacles, and servos press space (jump) and down arrow (duck). In Guitar mode, a guitar board controls the dino over Bluetooth.

## Components
- STM32F411CEU6 Black Pill
- 2 × GL5528 photoresistors + 10 kΩ resistors
- 2 × SG90 servos
- SSD1306 OLED (0.96")
- 2 × HC-05 Bluetooth modules
- Push button, breadboard power module, capacitors
- microSD card module (planned)

## Peripherals
| Peripheral | Use |
|---|---|
| ADC + DMA, TIM2 | Reading photoresistors (PA1, PB0) |
| TIM4 PWM | Servos (PB8, PB9) |
| I2C1 | OLED (PB6, PB7) |
| USART1 | Bluetooth (PA9, PA10), 9600 baud |
| GPIO / EXTI | KEY (PA0), START (PB12), LED (PC13) |
| IWDG | Watchdog |
| SPI1 | SD card (planned) |

## Progress
| Part | What | Status |
|---|---|---|
| 1 | LED and mode button | Done |
| 2 | Jump and duck servos | Done |
| 3 | OLED screen | Done |
| 4 | Bluetooth link | Done |
| 5 | Watchdog | Done |
| 6 | Reading photoresistors | Done |
| 7 | Jumping over cacti | Done |
| 8 | START button + auto calibration | Done |
| 9 | Ducking under birds | Done |
| 10 | Game over detection | Done |
| 11 | SD card logging | Next |

## How it works
- LDR A (ground level) gets dark when a cactus comes → jump.
- LDR C (head level) gets dark but LDR A stays bright → bird → duck.
- At START, the board measures the screen brightness and sets the threshold by itself.
- If nothing passes for 5 s, the game is over → back to PRESS START.
- Guitar mode: 'H' = jump, 'L' = duck, sent over Bluetooth.

## Note
For the demo, the game speed is fixed from the browser console, because the game speeds up in a way that depends on the monitor refresh rate:
```js
r = Runner.getInstance(); r.config.acceleration = 0; r.config.speed = 9; r.currentSpeed = 9
```

**Course:** ENGS 251 – Embedded Systems Project
