# AzureIoTHub - Azure IoT Hub library for Arduino

[![Build Status](https://travis-ci.org/arduino-libraries/AzureIoT.svg?branch=master)](https://travis-ci.org/arduino-libraries/AzureIoT)

This library is a port of the [Microsoft Azure IoT device SDK for C](https://github.com/Azure/azure-iot-sdks/blob/master/c/readme.md) to Arduino. It allows you to use several Arduino compatible boards with Azure IoT Hub.

Currently supported hardware:
- Atmel SAMD Based boards
  - Arduino/Genuino [MKR1000](https://www.arduino.cc/en/Main/ArduinoMKR1000)
  - Arduino/Genuino [Zero](https://www.arduino.cc/en/Main/ArduinoBoardZero) and [WiFi Shield 101](https://www.arduino.cc/en/Main/ArduinoWiFiShield101) 
  - Adafruit [Feather M0](https://www.adafruit.com/products/3010)
- ESP8266 based boards with [esp8266/arduino](https://github.com/esp8266/arduino)
  - SparkFun [Thing](https://www.sparkfun.com/products/13711)
  - Adafruit [Feather Huzzah](https://www.adafruit.com/products/2821)

[![Microsoft Azure Certified][Microsoft-Azure-Certified-Badge]][azure-certifiedforiot]

## Prerequisites

You should have the following ready before beginning with any board:
-   [Setup your IoT hub](https://github.com/Azure/azure-iot-sdks/blob/master/doc/setup_iothub.md)
-   [Provision your device and get its credentials](https://github.com/Azure/azure-iot-sdks/blob/master/doc/manage_iot_hub.md)
-   [Arduino IDE 1.6.8](https://www.arduino.cc/en/Main/Software)
-   Install the `AzureIoTHub` library via the Arduino IDE Library Manager

## MKR1000 or Zero + Wifi101
1. Open the AzureIoTHub SAMD sample from the Arduino IDE File->Examples menu.
2. Update Wifi SSID/Password in simplesample_http.ino 
    * Ensure you are using a wifi network that does not require additional manual steps after connection, such as opening a web browser.
3. Update IoT Hub Connection string in simplesample_http.c

## ESP8266
##### Sparkfun Thing, Adafruit Feather Huzzah, or generic ESP8266 board

1. Install esp8266 board support into your Arduino IDE.
    * Start Arduino and open Preferences window.
    * Enter `http://arduino.esp8266.com/stable/package_esp8266com_index.json` into Additional Board Manager URLs field. You can add multiple URLs, separating them with commas.
    * Open Boards Manager from Tools > Board menu and install esp8266 platform 2.1.0 or later 
    * Select your ESP8266 board from Tools > Board menu after installation
    
2. Open the AzureIoTHub ESP8266 sample from the Arduino IDE File->Examples menu.
3. Update Wifi SSID/Password in simplesample_http.ino 
    * Ensure you are using a wifi network that does not require additional manual steps after connection, such as opening a web browser.
4. Update IoT Hub Connection string in simplesample_http.c


## Adafruit Feather M0
1. Install Feather M0 board support into your Arduino IDE.
    * Start Arduino and open Preferences window.
    * Enter `https://adafruit.github.io/arduino-board-index/package_adafruit_index.json` into Additional Board Manager URLs field. You can add multiple URLs, separating them with commas.
    * Open Boards Manager from Tools > Board menu and install Adafruit SAMD Boards 1.0.7 or later.
    * Select your Adafruit Feather M0 from Tools > Board menu after installation
2. Install the [Adafruit WINC1500 wifi library](https://learn.adafruit.com/adafruit-feather-m0-wifi-atwinc1500/using-the-wifi-module)
3. Install the `RTCZero` library from the Arduino IDE Library Manager.
2. Open the AzureIoTHub SAMD sample from the Arduino IDE File->Examples menu.
3. Update Wifi SSID/Password in simplesample_http.ino 
    * Ensure you are using a wifi network that does not require additional manual steps after connection, such as opening a web browser.
4. Update IoT Hub Connection string in simplesample_http.c

## License

See [LICENSE](LICENSE) file.

[azure-certifiedforiot]:  http://azure.com/certifiedforiot 
[Microsoft-Azure-Certified-Badge]: images/Microsoft-Azure-Certified-150x150.png (Microsoft Azure Certified)
