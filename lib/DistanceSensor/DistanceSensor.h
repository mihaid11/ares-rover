#pragma once
#include "Arduino.h"

class DistanceSensor {
public:
    DistanceSensor(uint8_t trigPin, uint8_t echoPin);

    void setup();
    void update(unsigned long interval = 500);
    double getDistance() const;

private:
    uint8_t m_trigPin, m_echoPin;
    unsigned long m_lastReadTime;
    double m_lastDistance;

    void trigger();
    double readDistance();
};
