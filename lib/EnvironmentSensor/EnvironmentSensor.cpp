#include "EnvironmentSensor.h"

EnvironmentSensor::EnvironmentSensor(uint8_t datPin) :
    m_dht(datPin, DHT22) {}

void EnvironmentSensor::setup() {
    m_dht.begin();
}

float EnvironmentSensor::readTemperature() {
    float temp = m_dht.readTemperature();
    
    if (isnan(temp))
        return -1;
    return temp;
}

float EnvironmentSensor::readHumidity() {
    float humid = m_dht.readHumidity();

    if (isnan(humid))
        return -1;
    return humid;
}