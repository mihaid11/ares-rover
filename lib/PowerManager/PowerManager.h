#pragma once
#include <Arduino.h>
#include <Adafruit_INA219.h>

class PowerManager {
public:
    PowerManager();

    void setup();

    float getVoltage();
    float getCurrent();
    float getPower();
    int getBatteryPercentage();

private:
    Adafruit_INA219 m_ina;
};
