#include "DisplayManager.h"

DisplayManager::DisplayManager(uint8_t sdaPin, uint8_t sclPin) :
    m_lcd(0x27, 16, 2), m_sdaPin(sdaPin), m_sclPin(sclPin) {}

void DisplayManager::setup() {
    Wire.begin(m_sdaPin, m_sclPin);

    m_lcd.init();
    m_lcd.backlight();
    m_lcd.clear();
}

void DisplayManager::update(int mode, float temp, float humid, float distFront, float distBack, int speed) {
    if (mode >= 0 && mode <= 2)
        m_lcd.backlight();

    switch (mode) {
        case 0:
            renderEnvironment(temp, humid);
            break;
        case 1:
            renderDistances(distFront, distBack);
            break;
        case 2:
            renderTelemetry(speed, 0);
            break;
        default:
            m_lcd.noBacklight();
            m_lcd.clear();
            break;
    }
}

void DisplayManager::renderEnvironment(float temp, float humid) {
    char buffer[17];

    snprintf(buffer, sizeof(buffer), "Temp: %.1f C                ", temp);
    m_lcd.setCursor(0, 0);
    m_lcd.print(buffer);
    
    snprintf(buffer, sizeof(buffer), "Humid: %.1f %%                ", humid);
    m_lcd.setCursor(0, 1);
    m_lcd.print(buffer);
}

void DisplayManager::renderDistances(float distFront, float distBack) {
    char buffer[17];

    snprintf(buffer, sizeof(buffer), "Front: %.1f cm                ", distFront);
    m_lcd.setCursor(0, 0);
    m_lcd.print(buffer);
    
    snprintf(buffer, sizeof(buffer), "Back: %.1f cm                ", distBack);
    m_lcd.setCursor(0, 1);
    m_lcd.print(buffer);
}

void DisplayManager::renderTelemetry(int speed, int mode) {
    char buffer[17];

    snprintf(buffer, sizeof(buffer), "Speed: %d                ", speed);
    m_lcd.setCursor(0, 0);
    m_lcd.print(buffer);
    
    snprintf(buffer, sizeof(buffer), "Mode: %d                ", mode);
    m_lcd.setCursor(0, 1);
    m_lcd.print(buffer);
}