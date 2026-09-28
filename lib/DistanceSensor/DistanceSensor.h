#pragma once
#include "Arduino.h"

class DistanceSensor {
public:
    DistanceSensor(uint8_t trigPin, uint8_t echoPin);

    void setup();
    void update(unsigned long interval = 100);

    double getDistance() const;

private:
    uint8_t m_trigPin, m_echoPin;
    unsigned long m_lastReadTime, m_lastDistanceTime;
    double m_lastDistance;

    void trigger();

    volatile unsigned long m_echoStart;
    volatile unsigned long m_echoDuration;
    volatile bool m_dataReady;

    static void IRAM_ATTR isr_handler(void* arg);
    void IRAM_ATTR handleEcho();
};
