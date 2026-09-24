#include <Arduino.h>
#include "PinConfig.h"
#include "Button.h"
#include "DisplayManager.h"
#include "DistanceSensor.h"
#include "EnvironmentSensor.h"
#include "InertialSensor.h"
#include "MotorControl.h"
#include "PowerManager.h"

enum RoverState {
  STATE_IDLE,
  STATE_RC_MODE
};

RoverState current_mode = STATE_IDLE;

MotorControl motor(in1, in2, in3, in4, enA, enB);
DistanceSensor front_dist(front_trig, front_echo);
DistanceSensor back_dist(back_trig, back_echo);
EnvironmentSensor dht(dht_data);
InertialSensor mpu;
PowerManager ina;
DisplayManager display;

Button nav_button(btn_nav);
Button action_button(btn_action);

void setup() {
  Serial.begin(115200);
  Wire.begin(i2c_sda, i2c_scl);

  motor.setup();
  motor.setCalibration(1.f, 0.97f);
  motor.stop();

  front_dist.setup();
  back_dist.setup();
  dht.setup();
  ina.setup();
  mpu.setup();
  display.setup();

  nav_button.setup();
  action_button.setup();
}

void loop() {
  front_dist.update(500);
  back_dist.update(500);
  dht.update(2000);
  mpu.update(50);
  ina.update(700);
  display.update(0, dht.getTemperature(), dht.getHumidity(), front_dist.getDistance(), back_dist.getDistance(),
    motor.getCurrentSpeed(), ina.getVoltage(), ina.getBatteryPercentage(), ina.getCurrent(), ina.getPower());

  if (action_button.isPressed()) {
    current_mode = static_cast<RoverState>((current_mode + 1) % 2);
    motor.brake();
  }
}
