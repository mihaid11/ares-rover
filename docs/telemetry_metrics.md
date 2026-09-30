# Telemetry and metrics

This document outlines how the Ares Rover collects, processes and transmits real-time data to the user interface.

## Asynchronous web server
The rover hosts its own WiFi access point and web server.
- **JSON endpoints**: The ESP32 exposes dedicated endpoints (`/distance`, `/power`, `/env`, `/inertial`).
- **Client side polling**: The frontend script uses `fetch()` to request data asynchronously. This ensures the web interface remains fully responsive to user input while telemetry updates in the background.

## Metrics monitored
The system aggregates data from multiple subsystems to provide a complete view of the rover's state.
- **Spatial data (MPU6050)**: 6-axis tracking (3-axis accelerometer, 3-axis gyroscope). Used primarily for the yaw lock assist but exposed to the UI for future mapping or tilt warning features.
- **Environmental data (DHT22)**: Tracks ambient temperature and humidity. Used for calculating the speed of sound for more accurate proximity data.
- **Proximity data (HC-SR04)**: Front and rear distance metrics.
- **Power data (INA219)**: Real-time voltage, current, power and a calculated battery percentage based on the Li-Ion discharge curve.

### Straight-line assist bechmark
To evaluate the effectiveness of the MPU6050 yaw-lock algorithm, the rover was tested on a smooth surface over a fixed distance of **250cm** at a target speed of **180 PWM**.

| Configuration | Mean lateral drift | Drift percentage | Drift angle |
| --- | --- | --- | --- |
| Uncalibrated | 56.3cm | 22.52% | 12.69° |
| Static calibration (0.97 offset) | 27.6cm | 11.04% | 6.30° |
| P-Controller (Kp = 3.0) | 17.7cm | 7.08% | 4.05° |
| PID Controller | **In progress** | **In progress** | **In progress** |

## Dynamic data polling
To prevent network congestion, the telemetry system decouples the hardware tick rate from the network tick rate.
- **Hardware layer**: Sensors are read at high speeds to ensure the autonomous braking and steering systems have real-time data.
- **Network layer**: The web interface requests data at much slower intervals to save bandwidth and processor cycles. These UI intervals are further throttled when Eco mode is active.

### Polling intervals breakdown
The following table illustrates the dynamic intervals based on the active mode. Hardware intervals scale automatically depending on whether the rover is moving or stationary.

| Sensor | Hardware interval | Hardware interval Eco | Web UI interval | Web UI interval Eco |
| --- | --- | --- | --- | --- |
| Proximity (HC-SR04) | 80ms-500ms | 120ms-1000ms | 200ms | 500ms |
| Inertial (MPU6050) | 25ms-100ms | 50ms-1000ms | 500ms | 2000ms |
| Power (INA219) | 700ms | 3000ms | 700ms | 3000ms |
| Environment (DHT22) | 2000ms | 60000ms | 2000ms  | 60000ms |