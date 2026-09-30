# Ares Rover

An open-source 2WD rover built on the ESP32 platform, combining remote web control with active stability and safety systems. It features closed-loop yaw correction, ultrasonic emergency braking, real-time INA219 power monitoring, and an adaptive Eco mode.

## Features

| Function | Implementation |
| --- | --- |
| Environmental telemetry | Real-time temperature and humidity monitoring via AM2302 |
| Dynamic power management | Hardware sleep and sensor throttling based on active load |
| Spatial awareness | Front and rear ultrasonic distance measurement |
| Remote control | Manual override via wireless communication |

## Documentation
- [Hardware specifications](./docs/hardware_specs.md)
- [Software arhitecture](./docs/software_design.md)
- [Power management](./docs/power_management.md)
- [Telemetry and metrics](./docs/telemetry_metrics.md)

## License

Ares Rover is open source and distributed under the [MIT LICENSE](LICENSE).
