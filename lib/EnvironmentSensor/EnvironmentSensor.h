#pragma once
#include "Arduino.h"
#include "DHT.h"

class EnvironmentSensor {
public:
    EnvironmentSensor(uint8_t datPin);

    void setup();
    void update(unsigned long interval = 2000);

    float getTemperature();
    float getHumidity();
private:
    DHT m_dht;

    float m_lastTemp;
    float m_lastHumid;

    unsigned long m_lastReadTime;
};