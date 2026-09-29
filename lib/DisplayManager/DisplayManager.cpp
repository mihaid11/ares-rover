#include "DisplayManager.h"

constexpr unsigned long min_interval = 600;

DisplayManager::DisplayManager() :
    m_lcd(0x27, 16, 2), m_lastMode(0), m_lastUpdateTime(0), m_popoutTime(0), m_popoutActive(false) {}

void DisplayManager::setup() {
    m_lcd.init();
    m_lcd.backlight();
    m_lcd.clear();
}

void DisplayManager::showMessage(const char* text, unsigned long duration) {
    m_lcd.clear();
    m_lcd.setCursor(0, 0);
    m_lcd.print(text);

    m_popoutTime = millis() + duration;
    m_popoutActive = true;
}

void DisplayManager::update(int mode, float temp, float humid, float distFront, float distBack, int speed,
    float voltage, int batteryP, float current, float power, unsigned long interval) {
    unsigned long currentTime = millis();

    if (m_popoutActive) {
        if (currentTime < m_popoutTime) {
            return;
        } else {
            m_popoutActive = false;
            m_lcd.clear();
        }
    }

    if (currentTime - m_lastUpdateTime >= max(min_interval, interval) || mode != m_lastMode) {
        if (mode >= 0 && mode <= 3)
            m_lcd.backlight();

        switch (mode) {
            case 0:
                renderEnvironment(temp, humid);
                break;
            case 1:
                renderDistances(distFront, distBack);
                break;
            case 2:
                renderVoltage(voltage, batteryP);
                break;
            case 3:
                renderCurrent(current, power);
                break;
            default:
                m_lcd.noBacklight();
                m_lcd.clear();
                break;
        }

        m_lastMode = mode;
        m_lastUpdateTime = currentTime;
    }
}

void DisplayManager::setBacklight(bool state) {
    if (state)
        m_lcd.backlight();
    else
        m_lcd.noBacklight();
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

void DisplayManager::renderVoltage(float voltage, int batteryP) {
    char buffer[17];

    snprintf(buffer, sizeof(buffer), "Voltage: %.2f V                ", voltage);
    m_lcd.setCursor(0, 0);
    m_lcd.print(buffer);

    snprintf(buffer, sizeof(buffer), "Bat Per: %d %%                ", batteryP);
    m_lcd.setCursor(0, 1);
    m_lcd.print(buffer);
}

void DisplayManager::renderCurrent(float current, float power) {
    char buffer[17];

    snprintf(buffer, sizeof(buffer), "Current: %.1f mA                ", current);
    m_lcd.setCursor(0, 0);
    m_lcd.print(buffer);

    snprintf(buffer, sizeof(buffer), "Power: %.1f mW                ", power);
    m_lcd.setCursor(0, 1);
    m_lcd.print(buffer);
}
