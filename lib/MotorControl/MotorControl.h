#pragma once
#include <Arduino.h>

class MotorControl {
public:
    MotorControl(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4, uint8_t enA, uint8_t enB);

    void setup();
    void stop();
    void brake();

    void moveForward(uint8_t speed);
    void moveBackward(uint8_t speed);
    void turnLeft(uint8_t speed);
    void turnRight(uint8_t speed);

private:
    uint8_t m_in1, m_in2, m_in3, m_in4, m_enA, m_enB;
};