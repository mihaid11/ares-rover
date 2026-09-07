#include "Button.h"

Button::Button(uint8_t pin, unsigned long debounceDelay) :
    m_pin(pin), m_debounceDelay(debounceDelay), m_lastDebounceTime(0), m_lastButtonState(HIGH), m_buttonState(HIGH) {}

void Button::setup() {
    pinMode(m_pin, INPUT_PULLUP);
}

bool Button::isPressed() {
    bool reading = digitalRead(m_pin);
    bool pressed = false;

    if (reading != m_lastButtonState)
        m_lastDebounceTime = millis();

    if (millis() - m_lastDebounceTime > m_debounceDelay) {
        m_buttonState = reading;

        if (m_buttonState == LOW)
            pressed = true;
    }
    m_lastButtonState = reading;

    return pressed;
}