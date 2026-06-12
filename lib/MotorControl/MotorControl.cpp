#include <MotorControl.h>

MotorControl::MotorControl(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4, uint8_t enA, uint8_t enB)
    : m_in1(in1), m_in2(in2), m_in3(in3), m_in4(in4), m_enA(enA), m_enB(enB) {}

void MotorControl::begin() {
    pinMode(m_in1, OUTPUT);
    pinMode(m_in2, OUTPUT);
    pinMode(m_in3, OUTPUT);
    pinMode(m_in4, OUTPUT);

    pinMode(m_enA, OUTPUT);
    pinMode(m_enB, OUTPUT);

    stop();
}

void MotorControl::stop() {
    digitalWrite(m_in1, LOW);
    digitalWrite(m_in2, LOW);
    digitalWrite(m_in3, LOW);
    digitalWrite(m_in4, LOW);

    analogWrite(m_enA, 0);
    analogWrite(m_enB, 0);
}

void MotorControl::brake() {
    digitalWrite(m_in1, HIGH);
    digitalWrite(m_in2, HIGH);
    digitalWrite(m_in3, HIGH);
    digitalWrite(m_in4, HIGH);

    analogWrite(m_enA, 255);
    analogWrite(m_enB, 255);
}

void MotorControl::moveForward(uint8_t speed) {
    digitalWrite(m_in1, HIGH);
    digitalWrite(m_in2, LOW);
    digitalWrite(m_in3, HIGH);
    digitalWrite(m_in4, LOW);

    analogWrite(m_enA, speed);
    analogWrite(m_enB, speed);
}

void MotorControl::moveBackward(uint8_t speed) {
    digitalWrite(m_in1, LOW);
    digitalWrite(m_in2, HIGH);
    digitalWrite(m_in3, LOW);
    digitalWrite(m_in4, HIGH);

    analogWrite(m_enA, speed);
    analogWrite(m_enB, speed);
}

void MotorControl::turnLeft(uint8_t speed) {
    digitalWrite(m_in1, LOW);
    digitalWrite(m_in2, HIGH);
    digitalWrite(m_in3, HIGH);
    digitalWrite(m_in4, LOW);

    analogWrite(m_enA, speed);
    analogWrite(m_enB, speed);
}

void MotorControl::turnRight(uint8_t speed) {
    digitalWrite(m_in1, HIGH);
    digitalWrite(m_in2, LOW);
    digitalWrite(m_in3, LOW);
    digitalWrite(m_in4, HIGH);

    analogWrite(m_enA, speed);
    analogWrite(m_enB, speed);
}