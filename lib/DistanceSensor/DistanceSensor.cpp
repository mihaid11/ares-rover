#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(uint8_t trigPin, uint8_t echoPin)
    : m_trigPin(trigPin), m_echoPin(echoPin) {}

void DistanceSensor::setup() {
    pinMode(m_trigPin, OUTPUT);
    pinMode(m_echoPin, INPUT);
}

double DistanceSensor::readDistance() {
    digitalWrite(m_trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(m_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(m_trigPin, LOW);

    unsigned long time_elapsed = pulseIn(m_echoPin, HIGH, 400 / 0.0343);
    double distance = time_elapsed * 0.0343;

    return distance / 2;
}