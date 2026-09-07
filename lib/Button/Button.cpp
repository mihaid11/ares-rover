#include "Button.h"

Button::Button(uint8_t pin, unsigned long debounceDelay, unsigned long repeatDelay) :
    m_pin(pin), m_debounceDelay(debounceDelay), m_repeatDelay(repeatDelay), m_lastDebounceTime(0),
    m_lastRepeatTime(0), m_lastButtonState(HIGH), m_buttonState(HIGH) {}

void Button::setup() {
    pinMode(m_pin, INPUT_PULLUP);
}

bool Button::isPressed() {
    bool reading = digitalRead(m_pin);
    bool pressed = false;

    if (reading != m_lastButtonState)
        m_lastDebounceTime = millis();

    if (millis() - m_lastDebounceTime > m_debounceDelay) {
        if (reading != m_buttonState) {
            m_buttonState = reading;

            if (m_buttonState == LOW) {
                pressed = true;
                m_lastRepeatTime = millis();
            }
        } else if (m_buttonState == LOW) {
            if (millis() - m_lastRepeatTime >= m_repeatDelay) {
                pressed = true;
                m_lastRepeatTime = millis();
            }
        }
    }
    m_lastButtonState = reading;

    return pressed;
}