#include "EnvironmentSensor.h"

EnvironmentSensor::EnvironmentSensor(uint8_t datPin) :
    m_dht(datPin, DHT22), m_lastReadTime(0), m_lastTemp(0.f), m_lastHumid(0.f) {}

void EnvironmentSensor::setup() {
    m_dht.begin();
}

float EnvironmentSensor::readTemperature() {
    update();
    
    if (isnan(m_lastTemp))
        return -1;
    return m_lastTemp;
}

float EnvironmentSensor::readHumidity() {
    update();

    if (isnan(m_lastHumid))
        return -1;
    return m_lastHumid;
}

void EnvironmentSensor::update() {
    if (millis() - m_lastReadTime >= 2000) {
        m_lastTemp = m_dht.readTemperature();
        m_lastHumid = m_dht.readHumidity();

        m_lastReadTime = millis();
    }
}