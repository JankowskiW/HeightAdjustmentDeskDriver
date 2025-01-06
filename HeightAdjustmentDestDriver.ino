#include <Arduino.h>
#include "BluetoothHandler.h"
#include "PowerControl.h"
#include "ButtonControl.h"

#define ENABLE_12V_PIN 23
#define DEVICE_NAME "HEIGHT_ADJUSTMENT_DESK"

#define LEFT_ENCODER_PIN_A 12
#define LEFT_ENCODER_PIN_B 13

#define PIN 22

BluetoothHandler bluetoothHandler(DEVICE_NAME);
PowerControl powerControl(ENABLE_12V_PIN);
ButtonControl buttonControl(LEFT_ENCODER_PIN_A, INPUT_PULLDOWN, 10);

void handleBluetoothMessage(String message) {
    Serial.printf("Received message: %s\n", message.c_str());
    if (message == "0") {
        powerControl.setState(LOW);
    } else {
        powerControl.setState(HIGH);
    }
    powerControl.updateState();
}

void setup() {
    Serial.begin(115200);
    bluetoothHandler.begin(handleBluetoothMessage);
    powerControl.begin();

    buttonControl.init();
    pinMode(PIN, OUTPUT);
}

void loop() {
    bool state = buttonControl.readDigitalState();
    if (state) {
      digitalWrite(PIN, HIGH);
    } else {
      digitalWrite(PIN, LOW);
    }
}
