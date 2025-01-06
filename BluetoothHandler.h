#ifndef BLUETOOTH_HANDLER_H
#define BLUETOOTH_HANDLER_H

#include "BluetoothSerial.h"

#define MAX_BUFFER_SIZE 256

class BluetoothHandler {
public:
    BluetoothHandler(const char* deviceName) : deviceName(deviceName) {}

    void begin(void (*callback)(String)) {
        SerialBT.begin(deviceName);
        
        registerCallback();
        
        instance = this;
        messageCallback = callback;
        
        Serial.printf("The device is started.\nNow you can pair it with Bluetooth!\n");
    }

private:
    BluetoothSerial SerialBT;
    const char* deviceName;
    void (*messageCallback)(String) = nullptr; 

    static BluetoothHandler* instance;

    void registerCallback() {
      SerialBT.register_callback([](esp_spp_cb_event_t event, esp_spp_cb_param_t* param) {
        if (event == ESP_SPP_DATA_IND_EVT) {
          if (instance && instance->messageCallback) {
            char buffer[MAX_BUFFER_SIZE];
            int len = param->data_ind.len;
            if (len > (MAX_BUFFER_SIZE - 1)) {
              len = MAX_BUFFER_SIZE - 1;
            }
            strncpy(buffer, (char*)param->data_ind.data, len);
            buffer[len] = '\0';
            instance->messageCallback(String(buffer));
          }
       }
     });
   }
};
BluetoothHandler* BluetoothHandler::instance = nullptr;

#endif // BLUETOOTH_HANDLER_H
