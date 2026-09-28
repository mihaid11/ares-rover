#include "DistanceSensor.h"

// calculate the speed of sound with the default value of 20 degrees Celsius for now
constexpr float speed_of_sound = (331.3f + 0.606f * 20.f) / 10000.f;
constexpr unsigned long min_interval = 60;

DistanceSensor::DistanceSensor(uint8_t trigPin, uint8_t echoPin)
    : m_trigPin(trigPin), m_echoPin(echoPin), m_lastReadTime(0), m_lastDistance(0.0), m_echoStart(0),
    m_echoDuration(0), m_dataReady(false) {}

void DistanceSensor::setup() {
    pinMode(m_trigPin, OUTPUT);
    pinMode(m_echoPin, INPUT);

    attachInterruptArg(digitalPinToInterrupt(m_echoPin), isr_handler, this, CHANGE);
}

void DistanceSensor::update(unsigned long interval) {
    unsigned long current_time = millis();

    if (m_dataReady) {
        double dist = (m_echoDuration * speed_of_sound) / 2.;
        dist = constrain(dist, 2., 300.);

        m_lastDistance = dist;
        m_lastDistanceTime = current_time;
        m_dataReady = false;
    }

    if (current_time - m_lastReadTime >= max(min_interval, interval)) {
        trigger();
        m_lastReadTime = current_time;
    }
}

void DistanceSensor::trigger() {
    digitalWrite(m_trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(m_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(m_trigPin, LOW);
}

void IRAM_ATTR DistanceSensor::isr_handler(void* arg) {
    DistanceSensor* sensor = static_cast<DistanceSensor*>(arg);
    sensor->handleEcho();
}

void IRAM_ATTR DistanceSensor::handleEcho() {
    if (digitalRead(m_echoPin) == HIGH) {
        m_echoStart = micros();
    } else {
        m_echoDuration = micros() - m_echoStart;
        m_dataReady = true;
    }
}

double DistanceSensor::getDistance() const {
    return m_lastDistance;
}
