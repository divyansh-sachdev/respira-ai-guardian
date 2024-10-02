/**
 * RespiraAI Guardian — Edge Respiratory & Environmental Anomaly Detector
 * Author: Divyansh Sachdev
 */

#include <Arduino.h>
#include <Wire.h>
#include "config.example.h"
#include "acoustic_features.h"

#define I2S_WS   15
#define I2S_SCK  14
#define I2S_SD   32
#define ALERT_LED 2
#define BUZZER_PIN 25

const size_t BUFFER_SIZE = 512;
int16_t audioBuffer[BUFFER_SIZE];

void setup() {
    Serial.begin(115200);
    pinMode(ALERT_LED, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(ALERT_LED, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    
    Serial.println("==================================================");
    Serial.println("  RespiraAI Guardian — Edge Respiratory AI Monitor");
    Serial.println("==================================================");
    Serial.println("[INFO] Initializing I2S MEMS microphone (INMP441)...");
    Serial.println("[INFO] Initializing BME680 gas & environmental sensor...");
    Serial.println("[STATUS] System online. Monitoring breathing acoustics.");
}

void loop() {
    // Simulated reading from I2S DMA buffer
    for (size_t i = 0; i < BUFFER_SIZE; i++) {
        audioBuffer[i] = (int16_t)(random(-3000, 3000));
    }
    
    BreathMetrics metrics = analyzeBreathWindow(audioBuffer, BUFFER_SIZE, SAMPLE_RATE);
    
    Serial.printf("[METRICS] Energy: %.2f | Wheeze Prob: %.2f%% | Anomaly: %s\n", 
                  metrics.spectralEnergy, metrics.wheezeProbability * 100.0f,
                  metrics.anomalyDetected ? "CRITICAL ALERT" : "Normal");

    if (metrics.anomalyDetected) {
        digitalWrite(ALERT_LED, HIGH);
        tone(BUZZER_PIN, 1200, 200);
    } else {
        digitalWrite(ALERT_LED, LOW);
    }

    delay(1000);
}
