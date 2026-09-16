# Ares Rover

An open-source, autonomous 2WD rover built on the ESP32 platform, featuring environmental telemetry, obstacle avoidance, and dynamic power management.

## Features

| Function | Implementation |
| --- | --- |
| Environmental telemetry | Real-time temperature and humidity monitoring via AM2302 |
| Dynamic power management | Hardware sleep and sensor throttling based on active load |
| Spatial awareness | Front and rear ultrasonic distance measurement |
| Remote control | Manual override via wireless communication **(In progress)** |
| Autonomous maze solving | MPU6050-assisted 90-degree turning and wall following **(In progress)** |
| Line following | High-speed trajectory correction using a TCRT5000 sensor array **(In progress)** |

## Documentation
- [Hardware specifications](./docs/hardware_specs.md)
- [Software arhitecture](./docs/software_design.md)
- [Power management](./docs/power_management.md)
- [Telemetry and metrics](./docs/telemetry_metrics.md)