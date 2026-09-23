#include "PowerManager.h"

constexpr float max_battery_voltage = 8.4;
constexpr float min_battery_voltage = 6.6;

PowerManager::PowerManager() {}

void PowerManager::setup() {
    m_ina.begin();
}

float PowerManager::getVoltage() {
    return m_ina.getBusVoltage_V();
}

float PowerManager::getCurrent() {
    return m_ina.getCurrent_mA();
}

float PowerManager::getPower() {
    return m_ina.getPower_mW();
}

int PowerManager::getBatteryPercentage() {
    float v = getVoltage();

    if (v >= max_battery_voltage)
        return 100;
    if (v <= min_battery_voltage)
        return 0;

    return (int)((v - min_battery_voltage) / (max_battery_voltage - min_battery_voltage) * 100.0);
}
