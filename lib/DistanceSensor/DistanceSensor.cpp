#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(uint8_t trigPin, uint8_t echoPin)
    : m_trigPin(trigPin), m_echoPin(echoPin) {}

void DistanceSensor::setup() {
    pinMode(m_trigPin, OUTPUT);
    pinMode(m_echoPin, INPUT);
}