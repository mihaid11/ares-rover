# Hardware specifications

## Parts used

| Component | Qty | Power domain | Role |
| --- | --- | --- | --- |
| **ESP32 DevKit V1** | 1 | 3.3V Logic | Main processing unit and state machine controller |
| **[L298N](https://www.handsontec.com/dataspecs/L298N%20Motor%20Driver.pdf)** | 1 | 8.4V Power | Dual H-Bridge motor driver for differential steering |
| **TT DC Motors** | 2 | 6.0V - 8.4V | DC motors for locomotion |
| **[INA219](https://www.ti.com/lit/ds/symlink/ina219.pdf?ts=1789531969848)** | 1 | 3.3V Logic | Current and power monitor for eco mode triggers |
| **[MPU6050](https://www.hestore.hu/prod_getfile.php?id=8301)** | 1 | 3.3V Logic | Accelerometer and gyroscope for autonomous turning |
| **[HC-SR04](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf)** | 2 | 5.0V Logic | Ultrasonic sensors for front and read obstacle avoidance |
| **[AM2303 (DHT22)](https://cdn.sparkfun.com/assets/f/7/d/9/c/DHT22.pdf)** | 1 | 3.3V Logic | Temperature and humidity environmental sensor |
| **[LM2596](https://www.ti.com/lit/ds/symlink/lm2596.pdf)** | 1 | 8.4V $\rightarrow$ 5.0V | Buck converter supplying the 5V logic domain |
| **18650 Li-Ion** | 2 | 8.4V Power | 2-cell series battery pack providing system power |
| **Tactile button** | 1 | 3.3V Logic | Hardware input for mode selection |

## Pinout and Interfaces

| Signal | ESP32 Pin | Connected function |
| --- | --- | --- |
| `ENA` | `GPIO 32` | L298N Motor A PWM speed control |
| `IN1` | `GPIO 26` | L298N Motor A direction pin 1 |
| `IN2` | `GPIO 25` | L298N Motor A direction pin 2 |
| `ENB` | `GPIO 33` | L298N Motor B PWM speed control |
| `IN3` | `GPIO 27` | L298N Motor B direction pin 1 |
| `IN4` | `GPIO 14` | L298N Motor B direction pin 2 |
| `I2C_SDA` | `GPIO 21` | I<sup>2</sup>C data for LCD Display, MPU6050 IMU and INA219 PMIC |
| `I2C_SCL` | `GPIO 22` | I<sup>2</sup>C clock for LCD Display, MPU6050 IMU and INA219 PMIC |
| `DHT_DATA` | `GPIO 4` | AM2302 (DHT22) temperature and humidity data |
| `BTN_NAV` | `GPIO 19` | Polling pin for display menu transitions |
| `BTN_ACTION` | `GPIO 15` | Polling pin for state machine transitions |
| `FRONT_TRIG` | `GPIO 5` | Front HC-SR04 ultrasonic trigger pulse |
| `FRONT_ECHO` | `GPIO 18` | Front HC-SR04 ultrasonic echo pulse |
| `BACK_TRIG` | `GPIO 13` | Rear HC-SR04 ultrasonic trigger pulse |
| `BACK_ECHO` | `GPIO 17` | Rear HC-SR04 ultrasonic echo pulse |
