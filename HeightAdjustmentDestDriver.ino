#include <Arduino.h>
#include "BluetoothHandler.h"
#include "PowerControl.h"

#define ENABLE_12V_PIN 23
#define DEVICE_NAME "HEIGHT_ADJUSTMENT_DESK"

BluetoothHandler bluetoothHandler(DEVICE_NAME);
PowerControl powerControl(ENABLE_12V_PIN);

void setup() {
    Serial.begin(115200);
    bluetoothHandler.begin();
    powerControl.begin();
}

void loop() {
    if (bluetoothHandler.available()) {
        String message = bluetoothHandler.readMessage();
        if (message == "0") {
            powerControl.setState(LOW);
        } else {
            powerControl.setState(HIGH);
        }
    }
    powerControl.updateState();
    delay(10);
}
