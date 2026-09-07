#include "DistanceSensor.h"

// calculate the speed of sound with the default value of 20 degrees Celsius for now
constexpr float speed_of_sound = (331.3f + 0.606f * 20.f) / 10000.f;
constexpr unsigned long max_timeout = 400.f / speed_of_sound;

DistanceSensor::DistanceSensor(uint8_t trigPin, uint8_t echoPin)
    : m_trigPin(trigPin), m_echoPin(echoPin) {}

void DistanceSensor::setup() {
    pinMode(m_trigPin, OUTPUT);
    pinMode(m_echoPin, INPUT);
}

void DistanceSensor::trigger() {
    digitalWrite(m_trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(m_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(m_trigPin, LOW);
}

double DistanceSensor::readDistance() {
    trigger();

    unsigned long time_elapsed = pulseIn(m_echoPin, HIGH, max_timeout);
    double distance = time_elapsed * speed_of_sound;

    return distance / 2;
}