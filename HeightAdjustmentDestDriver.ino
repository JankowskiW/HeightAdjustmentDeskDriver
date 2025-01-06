#include <Arduino.h>
#include "BluetoothHandler.h"
#include "PowerControl.h"

#define ENABLE_12V_PIN 23
#define DEVICE_NAME "HEIGHT_ADJUSTMENT_DESK"

BluetoothHandler bluetoothHandler(DEVICE_NAME);
PowerControl powerControl(ENABLE_12V_PIN);

void handleBluetoothMessage(String message) {
    Serial.printf("Received message: %s\n", message.c_str());
    if (message == "0") {
        powerControl.setState(LOW);
    } else {
        powerControl.setState(HIGH);
    }
}

void setup() {
    Serial.begin(115200);
    bluetoothHandler.begin(handleBluetoothMessage);
    powerControl.begin();
}

void loop() {
    powerControl.updateState();
    delay(10);
}
