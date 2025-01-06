#ifndef BUTTON_CONTROL_H
#define BUTTON_CONTROL_H

#include <Arduino.h>
#include <set>

#define DEFAULT_PIN_MODE INPUT

using namespace std;

class ButtonControl {
public:
    ButtonControl(int pin, int modeOfPin, unsigned long debounceDelay) : pin(pin), modeOfPin(modeOfPin), lastState(LOW), lastDebounceTime(0), debounceDelay(debounceDelay) {}

    void init() {
        if (isModeAllowed(modeOfPin)) {
          pinMode(pin, modeOfPin);
        } else {
          pinMode(pin, DEFAULT_PIN_MODE);
          Serial.printf("Invalid mode was passed, the default one was set.");
        }
    }

    bool readDigitalState() {
        int buttonState = digitalRead(pin);

        if (buttonState != lastState) {
            lastDebounceTime = millis();
        }

        if ((millis() - lastDebounceTime) > debounceDelay) {
            if (buttonState != currentState) {
                currentState = buttonState;
            }
        }

        lastState = buttonState;
        
        return currentState;
    }


private:
    int pin;
    int modeOfPin;
    int lastState;
    int currentState = LOW;
    unsigned long debounceDelay;
    unsigned long lastDebounceTime;
    set<int> allowedModes = {INPUT, INPUT_PULLUP, INPUT_PULLDOWN};

    bool isModeAllowed(int modeOfPin) const {
      return allowedModes.find(modeOfPin) != allowedModes.end();
    }
};

#endif // BUTTON_CONTROL_H
