#include "PowerManager.h"

constexpr float max_battery_voltage = 8.4;
constexpr float min_battery_voltage = 6.6;
constexpr unsigned long min_interval = 200;

PowerManager::PowerManager() : m_lastReadTime(0), m_lastVoltage(0.f), m_lastCurrent(0.f), m_lastPower(0.f) {}

void PowerManager::setup() {
    m_ina.begin();
}

void PowerManager::update(unsigned long interval) {
    unsigned long current_time = millis();
    if (current_time - m_lastReadTime >= max(min_interval, interval)) {
        m_lastVoltage = m_ina.getBusVoltage_V();
        m_lastCurrent = m_ina.getCurrent_mA();
        m_lastPower = m_ina.getPower_mW();

        m_lastReadTime = current_time;
    }
}

float PowerManager::getVoltage() {
    return m_lastVoltage;
}

float PowerManager::getCurrent() {
    return m_lastCurrent;
}

float PowerManager::getPower() {
    return m_lastPower;
}

int PowerManager::getBatteryPercentage() {
    if (m_lastVoltage >= max_battery_voltage)
        return 100;
    if (m_lastVoltage <= min_battery_voltage)
        return 0;

    return (int)((m_lastVoltage - min_battery_voltage) / (max_battery_voltage - min_battery_voltage) * 100.0);
}
