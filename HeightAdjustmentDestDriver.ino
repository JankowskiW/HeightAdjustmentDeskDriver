#include <Arduino.h>
#include "BluetoothHandler.h"
#include "PowerControl.h"
#include "ButtonControl.h"
#include "EncoderControl.h"

#define ENABLE_12V_PIN 23
#define DEVICE_NAME "HEIGHT_ADJUSTMENT_DESK"

#define LEFT_ENCODER_PIN_A 12
#define LEFT_ENCODER_PIN_B 13

#define RIGHT_ENCODER_PIN_A 27
#define RIGHT_ENCODER_PIN_B 14

#define PIN 22

BluetoothHandler bluetoothHandler(DEVICE_NAME);
PowerControl powerControl(ENABLE_12V_PIN);
EncoderControl leftEncoderControl(LEFT_ENCODER_PIN_A, LEFT_ENCODER_PIN_B);
EncoderControl rightEncoderControl(RIGHT_ENCODER_PIN_A, RIGHT_ENCODER_PIN_B);


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
}

int previousPositionL = -1;
int currentPositionL = 0;

int previousPositionR = -1;
int currentPositionR = 0;

void loop() {
  currentPositionL = leftEncoderControl.currentPosition;
  if (currentPositionL != previousPositionL) {
    previousPositionL = currentPositionL;
    Serial.printf("\nLEFT_ENCODER_POSITION: %d", currentPositionL);
  }
  
  currentPositionR = rightEncoderControl.currentPosition;
  if (currentPositionR != previousPositionR) {
    previousPositionR = currentPositionR;
    Serial.printf("\nRIGHT_ENCODER_POSITION: %d", currentPositionR);
  }
}
