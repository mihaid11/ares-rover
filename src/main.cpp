#include <Arduino.h>
#include "Button.h"

enum RoverState {
  STATE_IDLE,
  STATE_RC_MODE,
  STATE_LINE_FOLLOW
};

RoverState currentState = STATE_IDLE;
Button modeButton(19);

void setup() {
  Serial.begin(115200);
  modeButton.setup();
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