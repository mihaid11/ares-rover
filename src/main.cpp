#include <Arduino.h>
#include "PinConfig.h"
#include "Button.h"
#include "DisplayManager.h"
#include "DistanceSensor.h"
#include "EnvironmentSensor.h"

enum RoverState {
  STATE_IDLE,
  STATE_RC_MODE,
  STATE_LINE_FOLLOW
};

RoverState currentState = STATE_IDLE;

Button modeButton(btn_mode);
DisplayManager display(i2c_sda, i2c_scl);

DistanceSensor dist_front(front_trig, front_echo);
DistanceSensor dist_back(back_trig, back_echo);
EnvironmentSensor env(dht_data);

void setup() {
  Serial.begin(115200);

  modeButton.setup();
  dist_front.setup();
  dist_back.setup();
  env.setup();
  display.setup();
}

void loop() {
  if (modeButton.isPressed())
    currentState = static_cast<RoverState>((currentState + 1) % 3);

  switch (currentState) {
    case STATE_IDLE:
      break;

    case STATE_RC_MODE:
      // TODO: Implement RC Mode
      break;

    case STATE_LINE_FOLLOW:
      // TODO: Implement Line Follow Mode
      break;
  }
}