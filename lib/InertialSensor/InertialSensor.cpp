#include "InertialSensor.h"

constexpr unsigned long min_interval = 10;

InertialSensor::InertialSensor()
    : m_lastReadTime(0), m_accelerationX(0.f), m_accelerationY(0.f), m_accelerationZ(0.f),
    m_gyroX(0.f), m_gyroY(0.f), m_gyroZ(0.f) {}

void InertialSensor::setup() {
    m_mpu.begin();

    m_mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
    m_mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    m_mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void InertialSensor::update(unsigned long interval) {
    unsigned long current_time = millis();
    if (current_time - m_lastReadTime >= max(min_interval, interval)) {
        sensors_event_t acc, gyr, temp;
        m_mpu.getEvent(&acc, &gyr, &temp);

        m_accelerationX = acc.acceleration.x;
        m_accelerationY = acc.acceleration.y;
        m_accelerationZ = acc.acceleration.z;

        m_gyroX = gyr.gyro.x;
        m_gyroY = gyr.gyro.y;
        m_gyroZ = gyr.gyro.z;
        
        m_lastReadTime = current_time;
    }
}

float InertialSensor::getAccelerationX() const {
    return m_accelerationX;
}

float InertialSensor::getAccelerationY() const {
    return m_accelerationY;
}

float InertialSensor::getAccelerationZ() const {
    return m_accelerationZ;
}

float InertialSensor::getGyroX() const {
    return m_gyroX;
}

float InertialSensor::getGyroY() const {
    return m_gyroY;
}

float InertialSensor::getGyroZ() const {
    return m_gyroZ;
}
