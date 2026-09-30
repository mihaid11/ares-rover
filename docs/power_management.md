# Power management

This document details the energy storage, distribution and monitoring systems of the Ares Rover.

## Hardware architecture
- **Energy storage**: The rover is powered by 2x 18650 Lithium-Ion cells wired in series. This provides a nominal voltage of 7.4V and a peak of 8.4V when fully charged.
- **Power distribution**: The battery pack connects directly to the L298N motor driver to provide maximum current to the motors. The ESP32 and peripheral sensors are powered via the onboard voltage regulator.

## Telemetry and monitoring
Real-time power monitoring is handled by an INA219 current sensor communicating via the I2C bus.
- **Current and power sensing**: Placed inline with the main power circuit, the INA219 measures the total system draw in mA and total power in mW.
- **Voltage tracking**: The sensor monitors the main battery pack voltage.

## Software optimization
To maximize runtime, the rover features an Eco mode that reduces the base consumption of the system.
- **Radio and network throttling**: Reduces the ESP32 WiFi transmit power from 19dBm to 8.5dBm. Simultaneously, the Web UI increases its fetch intervals allowing the ESP32 to rest between requests.
- **Peripheral sleep**: The I2C LCD backlight is physically commanded to turn off.

### Power state profiles
The table below outlines the target power states based on the rover activity and Eco mode status.

| State | Hardware status | WiFi state | Current (mA) | Power (mW) |
| --- | --- | --- | --- | --- |
| Idle | Motors off, Display on, fast sensors | TX Power 19dBm | **In progress** | **In progress** |
| Eco idle | Motors off, Display off, throttled sensors | TX Power 8.5dBm | **In progress** | **In progress** |
| Active (Speed 1) | Motors 140 PWM | TX Power 19dBm | **In progress** | **In progress** |
| Eco active (Speed 1) | Motors 140 PWM | TX Power 8.5dBm | **In progress** | **In progress** |
| Active (Speed 2) | Motors 180 PWM | TX Power 19dBm | **In progress** | **In progress** |
| Eco active (Speed 2) | Motors 180 PWM | TX Power 8.5dBm | **In progress** | **In progress** |
| Active (Speed 3) | Motors 220 PWM | TX Power 19dBm | **In progress** | **In progress** |
| Active (Max throttle) | Motors 255 PWM | TX Power 19dBm | **In progress** | **In progress** |
