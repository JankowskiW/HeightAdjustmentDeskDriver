#ifndef POWER_CONTROL_H
#define POWER_CONTROL_H

#include <Arduino.h>

class PowerControl {
public:
    PowerControl(int pin) : controlPin(pin), currentState(LOW), previousState(LOW) {}

    void begin() {
        pinMode(controlPin, OUTPUT);
        digitalWrite(controlPin, currentState);
    }

    void setState(int state) {
      Serial.write(state);
        currentState = state;
    }

    void updateState() {
        if (previousState != currentState) {
            digitalWrite(controlPin, currentState);
            previousState = currentState;
        }
    }

private:
    int controlPin;
    int currentState;
    int previousState;
};

#endif // POWER_CONTROL_H
