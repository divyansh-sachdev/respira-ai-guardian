#ifndef CONFIG_H
#define CONFIG_H

// WiFi Configuration (optional telemetry)
#define WIFI_SSID     "YourWiFiSSID"
#define WIFI_PASSWORD "YourWiFiPassword"

// Acoustic & Environmental Thresholds
#define WHEEZE_FREQ_LOW   400   // Hz
#define WHEEZE_FREQ_HIGH  1600  // Hz
#define AQI_WARNING_VOC   500   // ppb
#define SAMPLE_RATE       16000 // 16kHz I2S audio

#endif
