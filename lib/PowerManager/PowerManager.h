#pragma once
#include <Arduino.h>
#include <Adafruit_INA219.h>

class PowerManager {
public:
    PowerManager();

    void setup();
    void update(unsigned long interval);

    float getVoltage();
    float getCurrent();
    float getPower();
    int getBatteryPercentage();

private:
    Adafruit_INA219 m_ina;
    unsigned long m_lastReadTime;

    float m_lastVoltage, m_lastCurrent, m_lastPower;
};
