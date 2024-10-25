# RespiraAI Guardian

AI-powered wearable & bedside respiratory monitor that combines edge acoustic analysis (I2S MEMS microphone) and air quality telemetry (BME680 VOC/temperature/humidity) to detect early indicators of asthma attacks, wheezing, and respiratory distress.

## Architecture

- **Acoustic Inference**: Continuously samples breathing sounds at 16 kHz using an INMP441 omnidirectional I2S microphone. Spectral band ratio and variance algorithms extract wheezing signatures in real time.
- **Environmental Context**: Tracks VOCs, CO2 equivalent, temperature, and humidity. Identifies airborne triggers known to exacerbate asthma symptoms.
- **Edge Alerting**: Onboard buzzer, visual LED status, and Bluetooth Low Energy (BLE) service for zero-latency bedside alerts without relying on internet connectivity.

## Hardware & Pinout

| Peripheral | ESP32 Pin | Interface | Function |
| --- | --- | --- | --- |
| INMP441 SCK | GPIO 14 | I2S Clock | Acoustic sampling |
| INMP441 WS  | GPIO 15 | I2S Word Select | Left/Right channel select |
| INMP441 SD  | GPIO 32 | I2S Data In | 24-bit audio stream |
| BME680 SDA  | GPIO 21 | I2C Data | VOC & ambient monitoring |
| BME680 SCL  | GPIO 22 | I2C Clock | VOC & ambient monitoring |
| Alert Buzzer| GPIO 25 | PWM Output | Immediate audible warning |
| Status LED  | GPIO 2  | Digital Out | Normal / Alert indicator |

## Setup & Flashing

1. Open Arduino IDE or PlatformIO.
2. Install dependencies:
   - `Adafruit BME680 Library`
   - `ESP32-audioI2S`
3. Copy `config.example.h` to `config.h` and tune sensitivity if necessary.
4. Select `ESP32 Dev Module` and flash at 115200 baud.

## Disclaimer

Prototype developed for engineering research and robotics/IoT competitions. Not a certified medical device.
