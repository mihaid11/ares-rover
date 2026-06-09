#include <Arduino.h>

enum RoverState {
  STATE_IDLE,
  STATE_RC_MODE,
  STATE_LINE_FOLLOW
};

RoverState currentState = STATE_IDLE;
const int button_pin = 4;
bool lastButtonState = HIGH;
long lastDebounceTime = 0;

void setup() {
  Serial.begin(115200);
  pinMode(button_pin, INPUT_PULLUP);
}

void loop() {
  bool reading = digitalRead(button_pin);
  if (reading != lastButtonState && millis() - lastDebounceTime > 200) {
    if (reading == LOW)
      currentState = static_cast<RoverState>((currentState + 1) % 3);

    lastDebounceTime = millis();
  }
  lastButtonState = reading;

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