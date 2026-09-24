#pragma once
#include <Arduino.h>
#include "LiquidCrystal_I2C.h"

class DisplayManager {
public:
    DisplayManager();

    void setup();
    void update(int mode, float temp, float humid, float distFront, float distBack, int speed,
        float voltage, int batteryP, float current, float power, unsigned long interval = 600);

private:
    LiquidCrystal_I2C m_lcd;

    unsigned long m_lastUpdateTime;
    int m_lastMode;

    void renderEnvironment(float temp, float humid);
    void renderDistances(float distFront, float distBack);
    void renderVoltage(float voltage, int batteryP);
    void renderCurrent(float current, float power);
};
