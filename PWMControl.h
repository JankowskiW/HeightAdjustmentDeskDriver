#ifndef PWM_CONTROL_H
#define PWM_CONTROL_H

#include <cmath>

#define TIMER_BITS 12
#define PWM_FREQUENCY 5000
#define PWM_RESOLUTION 8

class PWMControl {
public:
    PWMControl(int clockwisePin, int anticlockwisePin, int enablePin) : clockwisePin(clockwisePin), anticlockwisePin(anticlockwisePin), enablePin(enablePin), clockwiseDirection(true) {}

    void init() {
        pinMode(clockwisePin, OUTPUT);
        pinMode(anticlockwisePin, OUTPUT);
        pinMode(enablePin, OUTPUT);
        ledcAttach(clockwisePin, PWM_FREQUENCY, TIMER_BITS);
        ledcAttach(anticlockwisePin, PWM_FREQUENCY, TIMER_BITS);
        digitalWrite(enablePin, LOW);
    }

    void setDirection(bool clockwise) {
      clockwiseDirection = clockwise;
    }

    void writePWMValue(int percentageValue) {
      int value = convertValue(percentageValue);
      if (value <= 0) { 
        digitalWrite(enablePin, LOW);
      } else {
        digitalWrite(enablePin, HIGH);
      }
      if (clockwiseDirection) {
        ledcWrite(anticlockwisePin, 0);
        ledcWrite(clockwisePin, value);
      } else {
        ledcWrite(clockwisePin, 0);
        ledcWrite(anticlockwisePin, value);
      }
    }
    

private:
    int clockwisePin;
    int anticlockwisePin;
    int enablePin;
    bool clockwiseDirection;

    int convertValue(int percentageValue) {
      int maxValue = pow(2, PWM_RESOLUTION);
      return (percentageValue / 100.0) * maxValue;
    }
};

#endif // PWM_CONTROL_H 
