#include "EnvironmentSensor.h"

constexpr unsigned long min_interval = 2000;

EnvironmentSensor::EnvironmentSensor(uint8_t datPin) :
    m_dht(datPin, DHT22), m_lastReadTime(0), m_lastTemp(0.f), m_lastHumid(0.f) {}

void EnvironmentSensor::setup() {
    m_dht.begin();
}

void EnvironmentSensor::update(unsigned long interval) {
    unsigned long current_time = millis();
    if (current_time - m_lastReadTime >= max(min_interval, interval)) {
        m_lastTemp = m_dht.readTemperature();
        m_lastHumid = m_dht.readHumidity();

        m_lastReadTime = current_time;
    }
}

float EnvironmentSensor::getTemperature() {
    if (isnan(m_lastTemp))
        return -1;
    return m_lastTemp;
}

float EnvironmentSensor::getHumidity() {
    if (isnan(m_lastHumid))
        return -1;
    return m_lastHumid;
}
