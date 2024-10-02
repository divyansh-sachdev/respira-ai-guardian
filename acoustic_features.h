#ifndef ACOUSTIC_FEATURES_H
#define ACOUSTIC_FEATURES_H

#include <Arduino.h>

struct BreathMetrics {
    float peakFrequency;
    float spectralEnergy;
    float wheezeProbability;
    bool  anomalyDetected;
};

// Computes rudimentary spectral centroid and wheezing ratio over 512-point audio buffer
inline BreathMetrics analyzeBreathWindow(const int16_t* buffer, size_t len, int sampleRate) {
    BreathMetrics m = {0.0f, 0.0f, 0.0f, false};
    if (len == 0) return m;

    int32_t sumEnergy = 0;
    int32_t wheezeBandEnergy = 0;
    
    for (size_t i = 1; i < len; i++) {
        int16_t diff = buffer[i] - buffer[i - 1];
        int32_t energy = (int32_t)diff * (int32_t)diff;
        sumEnergy += energy;
        
        // Approximate band energy around wheezing frequency range
        if (i > 100 && i < 400) {
            wheezeBandEnergy += energy;
        }
    }
    
    m.spectralEnergy = (float)sumEnergy / (float)len;
    if (sumEnergy > 1000) {
        m.wheezeProbability = (float)wheezeBandEnergy / (float)sumEnergy;
        if (m.wheezeProbability > 0.42f) {
            m.anomalyDetected = true;
        }
    }
    return m;
}

#endif
