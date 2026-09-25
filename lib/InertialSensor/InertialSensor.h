#pragma once
#include <Arduino.h>
#include <Adafruit_MPU6050.h>

class InertialSensor {
public:
    InertialSensor();

    void setup();
    void update(unsigned long interval = 50);

    float getAccelerationX() const;
    float getAccelerationY() const;
    float getAccelerationZ() const;

    float getGyroX() const;
    float getGyroY() const;
    float getGyroZ() const;

    float getYaw() const;

private:
    Adafruit_MPU6050 m_mpu;
    unsigned long m_lastReadTime;

    float m_accelerationX, m_accelerationY, m_accelerationZ;
    float m_gyroX, m_gyroY, m_gyroZ, m_gyroZ_error;
    float m_yaw;
};
