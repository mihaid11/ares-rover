#pragma once
#include "LiquidCrystal_I2C.h"

class DisplayManager {
public:
    DisplayManager(uint8_t sdaPin = 21, uint8_t sclPin = 22);

    void setup();
    void update(int mode, float temp, float humid, float distFront, float distBack, int speed);

private:
    LiquidCrystal_I2C m_lcd;
    uint8_t m_sdaPin;
    uint8_t m_sclPin;

    void renderEnvironment(float temp, float humid);
    void renderDistances(float distFront, float distBack);
    void renderTelemetry(int speed, int state);
};