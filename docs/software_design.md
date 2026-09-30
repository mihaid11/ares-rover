# Software design

This document outlines the software design for the Ares Rover. The goal was to build a responsive, safe and power efficient system using real world automotive logic without blocking the ESP32 processor.

## Core system
The entire codebase is built using OOP and runs asynchronously.
- **Component classes**: Every hardware piece has its own dedicated class.
- **Time based updates**: Instead of forcing the processor to wait, each class has its own update method.
- **Hardware protection**: Every class has a hidden interval built in. Even if the main loop asks the sensor to read data faster, the class will ignore the request to prevent hardware crashes.

## Autonomous emergency braking
The rover doesn't just look at how far away a wall is, it calculates the time to collision to know exactly when to brake.
- **Data smoothing**: Ultrasonic sensors are noisy. To fix this, the code uses an EMA filter. It blends 60% of the new reading with 40% of the old reading.
- **Speed tracking**: The rover calculates approach speed by comparing the old distance to the new distance over time.
- **Dynamic reaction**:
    - If an obstacle is closer than 50cm and the rover is moving towards it, the system calculates the impact time.
    - If impact is in **1.2 seconds**, it lowers the motor power proportionally.
    - If impact is in **0.4 seconds**, it triggers an emergency stop and cuts de power.
- **Boot grace period**: When the ESP32 boots and negociates the WiFi AP connection, the processor experiences heavy load, leading to missed interrupts and false distance spikes. To prevent phantom braking, the AEB system utilizes a 5 second grace period at boot, ignoring speed calculations while the hardware and network stack warm up.

## Straight line assist
DC motors rarely spin at the exact same speed, causing the rover to drift left or right instead of driving straight.
- **Real time correction**: As the rover moves, the software constantly checks the yaw angle. If the rover drifts off-center, the code calculates the error and adjusts the power sent to the left and right wheels to push the rover back on a perfectly straight line.
- **Boot calibration**: At startup, the system enforces a calibration phase. The MPU6050 records resting values to calculate the initial Gyro Z error offset. This calibration is crucial for accurate real-time correction later on.

## Eco mode
- **Reduced network traffic**: The web interface automatically slows down its data requests.
- **Dynamic sensor throttling**: The sensors are updated at dynamic intervals based on the rover state and its needs at the time.
- **Hardware sleep**: When Eco mode is active, the WiFi transmit power is reduced, the physical LCD backlight is turned off and the top speed is capped at a lower PWM.
