# Home Automation System

![Arduino](https://img.shields.io/badge/Arduino-Uno-00979D?style=for-the-badge\&logo=arduino\&logoColor=white)
![C++](https://img.shields.io/badge/Language-C++-00599C?style=for-the-badge\&logo=cplusplus\&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

This repository contains a simple Arduino-based home automation system sketch `home_automation_system.ino` that demonstrates sensor-driven control of lights, a fan, and an alert/buzzer, plus remote control over Bluetooth (HC-05).

## Features

- Read temperature using a DHT11 sensor and automatically turn on an AC indicator when temperature is above ~27.8°C.
- Read ambient light using an LDR and control a light relay/indicator based on brightness and a "night mode" flag.
- Passive infrared (IR) sensor for motion detection; triggers buzzer when in lock mode.
- Control a fan, lock mode, and night/day modes via Bluetooth HC-05 module by sending text commands.
- Serial debug output for temperature readings.

## Wiring / Hardware

Connections are expressed for a standard Arduino Uno. Adjust pins if you're using a different board.

- HC-05 Bluetooth module:
  - HC-05 TX -> Arduino pin 11 (BT RX)
  - HC-05 RX -> Arduino pin 10 (BT TX)
  - VCC -> 5V
  - GND -> GND

- DHT11 sensor:
  - Signal -> A1 (DHT_PIN)
  - VCC -> 5V
  - GND -> GND

- LDR (with voltage divider):
  - Analog output -> A0 (LDR_PIN)

- IR motion sensor:
  - Output -> Digital pin 3 (IR_SENSOR_PIN)

- Buzzer:
  - Positive -> Digital pin 4 (BUZZER_PIN)
  - Negative -> GND

- AC indicator LED (or relay control input):
  - Control -> Digital pin 5 (LED_AC)

- Light control LED/relay:
  - Control -> Digital pin 6 (LED_LIGHT)

- Fan control (through transistor/relay):
  - Control -> Digital pin 7 (FAN_PIN)

Notes:
- Use proper driver transistors, MOSFETs, or relays to drive high-current loads (fan, AC). Never drive motors or mains loads directly from Arduino pins.
- Use a common ground between sensors, Bluetooth module, and Arduino.

## Software / Libraries

The sketch uses the following libraries:

- SoftwareSerial (built-in)
- DHT (install via Library Manager; search for "DHT sensor library")

## Bluetooth Commands

Send plain text commands over the HC-05 serial connection (baud 9600):

- LOCK — enable lock mode (buzzer will sound on motion)
- UNLOCK — disable lock mode
- FAN — turn fan ON
- NOFAN — turn fan OFF
- NIGHT — enable night mode (forces light on when motion detected)
- DAY — disable night mode

Responses are sent back over Bluetooth to confirm actions.

## Configuration

- Temperature threshold is hard-coded to 27.8°C in the sketch (`if (temp > 27.8)`). Adjust in the code if needed.
- LDR darkness threshold is set to >700 (0-1023). Tune this value to match your lighting conditions.

## Uploading

1. Install the required libraries and connect your Arduino to the computer.
2. Open `home_automation_system.ino` in the Arduino IDE.
3. Select the correct board and serial port.
4. Upload the sketch.

## Troubleshooting

- If DHT readings return NaN, check wiring and try a different pin.
- If HC-05 communication fails, ensure TX/RX cross-connection and matching baud rate (9600).
- If the fan or AC won't run, check your relay/transistor wiring and power supply.

## License

This project is licensed under the **MIT License** and provided as-is for educational purposes. Feel free to modify and use it in your own projects.
