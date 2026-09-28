#include <MotorControl.h>

constexpr float wheel_diameter = 0.065f;
constexpr float max_rpm = 150.f;
constexpr float max_speed = max_rpm * (3.1415f * wheel_diameter) / 60.f;

MotorControl::MotorControl(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4, uint8_t enA, uint8_t enB)
    : m_in1(in1), m_in2(in2), m_in3(in3), m_in4(in4), m_enA(enA), m_enB(enB), m_currentPWM(0),
    m_leftOffset(1.f), m_rightOffset(1.f), m_targetYaw(0.f), m_lastCommand('S') {}

void MotorControl::setup() {
    pinMode(m_in1, OUTPUT);
    pinMode(m_in2, OUTPUT);
    pinMode(m_in3, OUTPUT);
    pinMode(m_in4, OUTPUT);

    pinMode(m_enA, OUTPUT);
    pinMode(m_enB, OUTPUT);

    stop();
}

void MotorControl::stop() {
    m_currentPWM = 0;

    digitalWrite(m_in1, LOW);
    digitalWrite(m_in2, LOW);
    digitalWrite(m_in3, LOW);
    digitalWrite(m_in4, LOW);

    analogWrite(m_enA, 0);
    analogWrite(m_enB, 0);
}

void MotorControl::brake() {
    m_currentPWM = 0;

    digitalWrite(m_in1, HIGH);
    digitalWrite(m_in2, HIGH);
    digitalWrite(m_in3, HIGH);
    digitalWrite(m_in4, HIGH);

    analogWrite(m_enA, 255);
    analogWrite(m_enB, 255);
}

void MotorControl::setCommand(char command, uint8_t speed) {
    m_currentCommand = command;
    m_targetSpeed = speed;

    if (m_currentCommand == 'S')
        brake();
}

void MotorControl::update(float yaw, float front_dist, float back_dist) {
    float min_dist = 5.f + ((float)m_targetSpeed / 255.f) * 10.f;

    if (m_currentCommand == 'F' && front_dist > 2.f) {
        if (front_dist <= min_dist) {
            brake();
            m_currentCommand = 'S';
            return;
        } else if (front_dist <= min_dist + 5.f) {
            stop();
            m_currentCommand = 'S';
            return;
        }
    }

    if (m_currentCommand == 'B' && back_dist > 2.f) {
        if (back_dist <= min_dist) {
            brake();
            m_currentCommand = 'S';
            return;
        } else if (front_dist <= min_dist + 5.f) {
            stop();
            m_currentCommand = 'S';
            return;
        }
    }

    if (m_currentCommand == 'F') {
        if (m_lastCommand != 'F')
            m_targetYaw = yaw;
        moveForward(m_targetSpeed, yaw);
    } else if (m_currentCommand == 'L') {
        turnLeft(m_targetSpeed);
    } else if (m_currentCommand == 'R') {
        turnRight(m_targetSpeed);
    } else if (m_currentCommand == 'B') {
        if (m_lastCommand != 'B')
            m_targetYaw = yaw;
        moveBackward(m_targetSpeed, yaw);
    }

    m_lastCommand = m_currentCommand;
}

void MotorControl::moveForward(uint8_t speed, float yaw) {
    m_currentPWM = speed;
    float Kp = 3.f;

    float error = m_targetYaw - yaw;
    int corr = (int)(Kp * error);
    corr = constrain(corr, -80, 80);

    int speedLeft = speed - corr;
    speedLeft = constrain(speedLeft, 0, 255);

    int speedRight = speed + corr;
    speedRight = constrain(speedRight, 0, 255);

    digitalWrite(m_in1, HIGH);
    digitalWrite(m_in2, LOW);
    digitalWrite(m_in3, HIGH);
    digitalWrite(m_in4, LOW);

    analogWrite(m_enA, speedLeft * m_leftOffset);
    analogWrite(m_enB, speedRight * m_rightOffset);
}

void MotorControl::moveBackward(uint8_t speed, float yaw) {
    m_currentPWM = speed;
    float Kp = 3.f;

    float error = m_targetYaw - yaw;
    int corr = (int)(Kp * error);
    corr = constrain(corr, -80, 80);

    int speedLeft = speed - corr;
    speedLeft = constrain(speedLeft, 0, 255);

    int speedRight = speed + corr;
    speedRight = constrain(speedRight, 0, 255);

    digitalWrite(m_in1, LOW);
    digitalWrite(m_in2, HIGH);
    digitalWrite(m_in3, LOW);
    digitalWrite(m_in4, HIGH);

    analogWrite(m_enA, speedLeft * m_leftOffset);
    analogWrite(m_enB, speedRight * m_rightOffset);
}

void MotorControl::turnLeft(uint8_t speed) {
    m_currentPWM = speed;

    digitalWrite(m_in1, LOW);
    digitalWrite(m_in2, HIGH);
    digitalWrite(m_in3, HIGH);
    digitalWrite(m_in4, LOW);

    analogWrite(m_enA, speed * m_leftOffset);
    analogWrite(m_enB, speed * m_rightOffset);
}

void MotorControl::turnRight(uint8_t speed) {
    m_currentPWM = speed;

    digitalWrite(m_in1, HIGH);
    digitalWrite(m_in2, LOW);
    digitalWrite(m_in3, LOW);
    digitalWrite(m_in4, HIGH);

    analogWrite(m_enA, speed * m_leftOffset);
    analogWrite(m_enB, speed * m_rightOffset);
}

float MotorControl::getCurrentSpeed() {
    return max_speed * (m_currentPWM / 255.f);
}

void MotorControl::setCalibration(float leftOffset, float rightOffset) {
    m_leftOffset = leftOffset;
    m_rightOffset = rightOffset;
}
