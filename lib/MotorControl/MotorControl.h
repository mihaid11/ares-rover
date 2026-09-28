#pragma once
#include <Arduino.h>

class MotorControl {
public:
    MotorControl(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4, uint8_t enA, uint8_t enB);

    void setup();
    void stop();
    void brake();

    void update(float yaw, float front_dist, float back_dist);
    void setCommand(char command, uint8_t speed);

    void moveForward(uint8_t speed, float yaw);
    void moveBackward(uint8_t speed, float yaw);
    void turnLeft(uint8_t speed);
    void turnRight(uint8_t speed);

    float getCurrentSpeed();
    void setCalibration(float leftOffset, float rightOffset);

private:
    uint8_t m_in1, m_in2, m_in3, m_in4, m_enA, m_enB;
    uint8_t m_currentPWM;

    char m_currentCommand, m_lastCommand;
    uint8_t m_targetSpeed;
    float m_targetYaw;
    float m_leftOffset, m_rightOffset;
};
