#pragma once
#include "Arduino.h"
#include "DHT.h"

class EnvironmentSensor {
public:
    EnvironmentSensor(uint8_t datPin);

    void setup();
    float readTemperature();
    float readHumidity();
private:
    DHT m_dht;
};