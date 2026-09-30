#include "InertialSensor.h"

constexpr unsigned long min_interval = 10;

InertialSensor::InertialSensor()
    : m_lastReadTime(0), m_accelerationX(0.f), m_accelerationY(0.f), m_accelerationZ(0.f),
    m_gyroX(0.f), m_gyroY(0.f), m_gyroZ(0.f), m_gyroZ_error(0.f), m_yaw(0.f) {}

void InertialSensor::setup() {
    m_mpu.begin();

    m_mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
    m_mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    m_mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

    float sum = 0;
    for (int i  = 0; i < 200; ++i) {
        sensors_event_t acc, gyr, temp;
        m_mpu.getEvent(&acc, &gyr, &temp);
        sum += gyr.gyro.z;
        delay(10);
    }
    m_gyroZ_error = sum / 200.f;
    m_lastReadTime = millis();
}

void InertialSensor::update(unsigned long interval) {
    unsigned long current_time = millis();
    if (current_time - m_lastReadTime >= max(min_interval, interval)) {
        float dt = (current_time - m_lastReadTime ) / 1000.f;

        sensors_event_t acc, gyr, temp;
        m_mpu.getEvent(&acc, &gyr, &temp);

        m_accelerationX = acc.acceleration.x;
        m_accelerationY = acc.acceleration.y;
        m_accelerationZ = acc.acceleration.z;

        m_gyroX = gyr.gyro.x;
        m_gyroY = gyr.gyro.y;
        m_gyroZ = gyr.gyro.z;
        
        if (abs(gyr.gyro.z - m_gyroZ_error) > 0.015f)
            m_yaw += (gyr.gyro.z - m_gyroZ_error) * dt * (180.f / PI);

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

float InertialSensor::getYaw() const {
    return m_yaw;
}
