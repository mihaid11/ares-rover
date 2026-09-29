#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "WebPage.h"
#include "UI.h"

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
int display_mode = 0;
bool eco_mode = false;

MotorControl motor(in1, in2, in3, in4, enA, enB);
DistanceSensor front_dist(front_trig, front_echo);
DistanceSensor back_dist(back_trig, back_echo);
EnvironmentSensor dht(dht_data);
InertialSensor mpu;
PowerManager ina;
DisplayManager display;

Button nav_button(btn_nav);
Button action_button(btn_action);

WebServer server(80);

int dht_interval = 2000;
int ina_interval = 700;
int display_interval = 600;

void startWiFi() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP("AresRover", "12345678");
  server.begin();
}

void stopWiFi() {
  server.stop();
  WiFi.softAPdisconnect();
  WiFi.mode(WIFI_OFF);
}

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

  server.on("/", handleRoot);
  server.on("/action", handleAction);
  server.on("/distance", handleDistance);
  server.on("/power", handlePower);
  server.on("/env", handleEnvironment);
  server.on("/inertial", handleInertial);
  server.on("/eco", handleEco);
}

void loop() {
  front_dist.update(100);
  back_dist.update(100);
  dht.update(dht_interval);
  mpu.update(50);
  ina.update(ina_interval);
  display.update(display_mode, dht.getTemperature(), dht.getHumidity(), front_dist.getDistance(), back_dist.getDistance(),
    motor.getCurrentSpeed(), ina.getVoltage(), ina.getBatteryPercentage(), ina.getCurrent(), ina.getPower(), display_interval);

  if (nav_button.isPressed())
    display_mode = (display_mode + 1) % 5;

  if (action_button.isPressed()) {
    current_mode = static_cast<RoverState>((current_mode + 1) % 2);
    motor.brake();

    if (current_mode == STATE_IDLE) {
      stopWiFi();
      display.showMessage("Idle Mode");
    } else if (current_mode == STATE_RC_MODE) {
      startWiFi();
      display.showMessage("RC Mode");
    }
  }

  if (current_mode == STATE_RC_MODE) {
    motor.update(mpu.getGyroZ(), front_dist.getDistance(), front_dist.getVelocity(), back_dist.getDistance(), back_dist.getVelocity(), eco_mode);
    server.handleClient();
  }
}
