#pragma once
#include "Arduino.h"

class DistanceSensor {
public:
    DistanceSensor(uint8_t trigPin, uint8_t echoPin);

    void setup();
    double readDistance();

private:
    uint8_t m_trigPin, m_echoPin;
};