#ifndef BLUETOOTH_HANDLER_H
#define BLUETOOTH_HANDLER_H

#include "BluetoothSerial.h"

class BluetoothHandler {
public:
    BluetoothHandler(const char* deviceName) : deviceName(deviceName) {}

    void begin() {
        SerialBT.begin(deviceName);
        Serial.printf("The device is started.\nNow you can pair it with Bluetooth!\n");
    }

    bool available() {
        return SerialBT.available();
    }

    String readMessage() {
        String incomingMessage = "";
        while (SerialBT.available()) {
            char c = (char)SerialBT.read();
            incomingMessage += c;
        }
        return incomingMessage;
    }

private:
    BluetoothSerial SerialBT;
    const char* deviceName;
};

#endif // BLUETOOTH_HANDLER_H
