#pragma once
#include "Arduino.h"

class Button {
public:
    Button(uint8_t pin, unsigned long debounceDelay = 50, unsigned long repeatDelay = 650);

    void setup();
    bool isPressed();

private:
    uint8_t m_pin;
    unsigned long m_debounceDelay;
    unsigned long m_repeatDelay;

    unsigned long m_lastDebounceTime;
    unsigned long m_lastRepeatTime;
    bool m_lastButtonState;
    bool m_buttonState;
};