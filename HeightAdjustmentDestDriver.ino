#include <Arduino.h>
#include "BluetoothHandler.h"
#include "PowerControl.h"
#include "ButtonControl.h"
#include "EncoderControl.h"
#include "PWMControl.h"

#define ENABLE_12V_PIN 23
#define DEVICE_NAME "HEIGHT_ADJUSTMENT_DESK"

#define LEFT_ENCODER_PIN_A 12
#define LEFT_ENCODER_PIN_B 13

#define RIGHT_ENCODER_PIN_A 27
#define RIGHT_ENCODER_PIN_B 14

#define LEFT_PWM_CLOCKWISE_PIN 15
#define LEFT_PWM_ANTICLOCKWISE_PIN 2
#define LEFT_PWM_ENABLE_PIN 4

#define RIGHT_PWM_CLOCKWISE_PIN 16
#define RIGHT_PWM_ANTICLOCKWISE_PIN 17
#define RIGHT_PWM_ENABLE_PIN 5

BluetoothHandler bluetoothHandler(DEVICE_NAME);

PowerControl powerControl(ENABLE_12V_PIN);

EncoderControl leftEncoderControl(LEFT_ENCODER_PIN_A, LEFT_ENCODER_PIN_B);
EncoderControl rightEncoderControl(RIGHT_ENCODER_PIN_A, RIGHT_ENCODER_PIN_B);

PWMControl leftPWMControl(LEFT_PWM_CLOCKWISE_PIN, LEFT_PWM_ANTICLOCKWISE_PIN, LEFT_PWM_ENABLE_PIN);
PWMControl rightPWMControl(RIGHT_PWM_CLOCKWISE_PIN, RIGHT_PWM_ANTICLOCKWISE_PIN, RIGHT_PWM_ENABLE_PIN);


void handleBluetoothMessage(String message) {
    Serial.printf("Received message: %s\n", message.c_str());
    if (message == "0") {
        powerControl.setState(LOW);
    } else {
        powerControl.setState(HIGH);
    }
    powerControl.updateState();
}

void IRAM_ATTR handleLeftEncoderPositionChange() {
  leftEncoderControl.updateCurrentPosition();
}

void IRAM_ATTR handleRightEncoderPositionChange() {
  rightEncoderControl.updateCurrentPosition();
}


void setup() {
    Serial.begin(9600);
    bluetoothHandler.begin(handleBluetoothMessage);
    powerControl.begin();

    leftEncoderControl.init();
    attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER_PIN_A), handleLeftEncoderPositionChange, RISING);

    rightEncoderControl.init();
    attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER_PIN_A), handleRightEncoderPositionChange, RISING);

    leftPWMControl.init();
//    rightPWMControl.init();
    
    leftPWMControl.setDirection(true);
}

void loop() {
    int i = 0;
    for (; i < 100; i+=5) {
      leftPWMControl.writePWMValue(i);
      delay(50);
    }
    for (; i > 0; i-=5) {
      leftPWMControl.writePWMValue(i);
      delay(50);
    }
}
