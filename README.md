<div align="center">

# RespiraAI Guardian

**Edge acoustic respiratory monitor combining breath-sound analysis with air-quality context**

![Domain](https://img.shields.io/badge/Domain-Acoustic_Signal_Processing-00F3FF?style=for-the-badge) ![Platform](https://img.shields.io/badge/Platform-ESP32_Edge-9D00FF?style=for-the-badge) ![Audio](https://img.shields.io/badge/Audio-16_kHz_I2S-0066FF?style=for-the-badge)

![ESP32](https://img.shields.io/badge/ESP32-0D1117?style=flat-square&logo=espressif&logoColor=white) ![Arduino](https://img.shields.io/badge/Arduino-0D1117?style=flat-square&logo=arduino&logoColor=white) ![C++](https://img.shields.io/badge/C++-0D1117?style=flat-square&logo=cplusplus&logoColor=white) ![I2S](https://img.shields.io/badge/I2S-0D1117?style=flat-square) ![INMP441](https://img.shields.io/badge/INMP441-0D1117?style=flat-square) ![BME680](https://img.shields.io/badge/BME680-0D1117?style=flat-square) ![BLE](https://img.shields.io/badge/BLE-0D1117?style=flat-square)

</div>

---

## Overview

A bedside and wearable respiratory monitor that listens to breathing and watches the air at the same
time. Breath sounds are captured through an I2S MEMS microphone and reduced on-device to spectral
features associated with wheezing, while a BME680 tracks the VOC, temperature and humidity conditions
known to trigger asthma symptoms.

Both halves run locally on the ESP32 and alert over BLE, so the device keeps working with no internet
connection — which matters for something that sits next to a bed at 3am.

## Domain &amp; Techniques

| Layer | Implementation |
| :--- | :--- |
| **Acquisition** | INMP441 omnidirectional MEMS microphone streamed over I2S at 16 kHz into a 512-point analysis window |
| **Feature Extraction** | Per-window sample-difference energy accumulation, split into a total-energy term and a wheeze-band energy term |
| **Wheeze Scoring** | Band-energy ratio (wheeze band / total energy) produces a continuous wheeze probability rather than a binary trip |
| **Environmental Context** | BME680 supplies VOC, CO&#8322;-equivalent, temperature and humidity to distinguish a symptom event from an air-quality trigger |
| **Alerting** | On-board buzzer, status LED and a BLE service — zero-latency, no internet dependency |

## Pipeline

```
INMP441 mic --I2S 16 kHz--> 512-point window
                                  |
                      [ sample-difference energy ]
                                  |
                +-----------------+------------------+
                |                                    |
        total spectral energy               wheeze-band energy
                |                                    |
                +--------------> ratio --------------+
                                  |
                                  v
                        wheeze probability ---+
                                              |--> buzzer / LED / BLE alert
BME680 --> VOC, CO2e, temp, humidity ---------+
```

## Hardware &amp; Pinout

| Peripheral | ESP32 Pin | Interface | Function |
| --- | --- | --- | --- |
| INMP441 SCK | GPIO 14 | I2S Clock | Acoustic sampling |
| INMP441 WS  | GPIO 15 | I2S Word Select | Left/Right channel select |
| INMP441 SD  | GPIO 32 | I2S Data In | 24-bit audio stream |
| BME680 SDA  | GPIO 21 | I2C Data | VOC & ambient monitoring |
| BME680 SCL  | GPIO 22 | I2C Clock | VOC & ambient monitoring |
| Alert Buzzer| GPIO 25 | PWM Output | Immediate audible warning |
| Status LED  | GPIO 2  | Digital Out | Normal / Alert indicator |

## Setup &amp; Flashing

1. Open Arduino IDE or PlatformIO.
2. Install dependencies:
   - `Adafruit BME680 Library`
   - `ESP32-audioI2S`
3. Copy `config.example.h` to `config.h` and tune sensitivity if necessary.
4. Select `ESP32 Dev Module` and flash at 115200 baud.

## Repository Layout

| Path | Purpose |
| :--- | :--- |
| `RespiraAIGuardian.ino` | Main firmware — I2S capture, environmental polling, alert dispatch |
| `acoustic_features.h` | `analyzeBreathWindow()` — energy accumulation and wheeze-band ratio scoring |
| `config.example.h` | Sensitivity thresholds — copy to `config.h` |

## Project Status

**Implemented:** continuous 16 kHz I2S capture, time-domain band-energy feature extraction, wheeze
probability scoring, environmental context, local BLE/buzzer alerting.

**Roadmap:** the current feature extractor approximates band energy in the time domain; moving to a
proper FFT (or a CMSIS-DSP real FFT) would give true spectral bins and a sharper wheeze signature.
That, in turn, is the natural input for a small learned classifier trained on labelled breath audio.

> Prototype developed for engineering research and robotics/IoT competitions. Not a certified medical
> device.

---

<div align="center">
  <sub>
    Part of the <b>AI + Robotics</b> engineering portfolio of
    <a href="https://github.com/divyansh-sachdev">Divyansh Sachdev</a><br>
    90+ national &amp; international competition wins &middot; IIT / NIT / IIIT podiums
  </sub>
</div>
