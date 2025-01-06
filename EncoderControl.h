#ifndef ENCODER_CONTROL_H
#define ENCODER_CONTROL_H

#include <Arduino.h>

#define SIGNAL_PIN_MODE INPUT_PULLUP
#define SIGNAL_PIN_DEBOUNCE_DELAY 5

class EncoderControl {
public:
    EncoderControl(int pinSIA, int pinSIB) : pinSIA(pinSIA), pinSIB(pinSIB), currentPosition(0) {}
    
    int currentPosition;

    void init() {
      pinMode(pinSIA, SIGNAL_PIN_MODE);
      pinMode(pinSIB, SIGNAL_PIN_MODE);
    }

    void updateCurrentPosition() {
     if ((millis() - lastDebounceTime) > SIGNAL_PIN_DEBOUNCE_DELAY) {
        int stateA = digitalRead(pinSIA);
        int stateB = digitalRead(pinSIB);
  
        if (stateA == LOW) {
          if (stateB == HIGH) {
            currentPosition++;
          } else {
            currentPosition--;
          }
        }
    
        lastDebounceTime = millis();
      }
    }

    
private:
    int pinSIA;
    int pinSIB;
    int lastDebounceTime = 0;
};

#endif // ENCODER_CONTROL_H
