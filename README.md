This project has adopted the 
[Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/). 
For more information see the 
[Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or contact 
[opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.

# AzureIoTHub - Azure IoT Hub library for Arduino

This library is a port of the 
[Microsoft Azure IoT device SDK for C](https://github.com/Azure/azure-iot-sdks/blob/master/c/readme.md)
 to Arduino. It allows you to use several Arduino compatible boards with Azure IoT Hub.

## Contributors

### **Pull request caution!**
All of the files in these Arduino library directories are auto-generated
by the Azure IoT C SDK release process, so pull requests cannot be 
accepted in this repo. 
Your Arduino-specific contributions will be welcomed with open arms in these locations:
*  [AzureIoTHub Arduino-specific sources](https://github.com/Azure/azure-iot-pal-arduino/tree/master/build_all/base-libraries/AzureIoTHub)
*  [AzureIoTProtocol_HTTP sources](https://github.com/Azure/azure-iot-pal-arduino/tree/master/build_all/base-libraries/AzureIoTProtocol_HTTP)
*  [AzureIoTProtocol_MQTT Arduino-specific sources](https://github.com/Azure/azure-iot-pal-arduino/tree/master/build_all/base-libraries/AzureIoTProtocol_MQTT)
*  [AzureIoTUtility Arduino-specific sources](https://github.com/Azure/azure-iot-pal-arduino/tree/master/build_all/base-libraries/AzureIoTUtility)

Contributions for code that is not Arduino-specific can be made to the 
[Azuure IoT C SDK](https://github.com/azure/azure-iot-sdk-c)

## Currently supported hardware
- Atmel SAMD Based boards
  - Adafruit [Feather M0](https://www.adafruit.com/products/3010)
- ESP8266 based boards with [esp8266/arduino](https://github.com/esp8266/arduino)
  - SparkFun [Thing](https://www.sparkfun.com/products/13711)
  - Adafruit [Feather Huzzah](https://www.adafruit.com/products/2821)

## Prerequisites

You should have the following ready before beginning with any board:
-   [Setup your IoT hub](https://github.com/Azure/azure-iot-device-ecosystem/blob/master/setup_iothub.md)
-   [Provision your device and get its credentials](https://github.com/Azure/azure-iot-device-ecosystem/blob/master/setup_iothub.md#create-new-device-in-the-iot-hub-device-identity-registry)
-   [Arduino IDE 1.6.12](https://www.arduino.cc/en/Main/Software)
-   Install the [`AzureIoTHub`](https://github.com/Azure/azure-iot-arduino) library via the Arduino IDE Library Manager
-   Install the [`AzureIoTUtility`](https://github.com/Azure/azure-iot-arduino-utility) library via the Arduino IDE Library Manager
-   Install the [`AzureIoTProtocol_HTTP`](https://github.com/Azure/azure-iot-arduino-protocol-http) library via the Arduino IDE Library Manager


## Simple Sample Instructions

### ESP8266
##### Sparkfun Thing, Adafruit Feather Huzzah, or generic ESP8266 board

1. Install esp8266 board support into your Arduino IDE.
    * Start Arduino and open Preferences window.
    * Enter `http://arduino.esp8266.com/stable/package_esp8266com_index.json` into Additional Board Manager URLs field. You can add multiple URLs, separating them with commas.
    * Open Boards Manager from Tools > Board menu and install esp8266 platform 2.2.0 or later
    * Select your ESP8266 board from Tools > Board menu after installation

2. Open the `simplesample_http` example from the Arduino IDE  File->AzureIoTHub->ESP8266->Examples menu.
4. Update Wifi SSID/Password and IoT Hub Connection string in iot_configs.h
    * Ensure you are using a wifi network that does not require additional manual steps after connection, such as opening a web browser.
6. Access the [SparkFun Get Started](https://azure.microsoft.com/en-us/documentation/samples/iot-hub-c-thingdev-getstartedkit/) tutorial to learn more about Microsoft Sparkfun Dev Kit.
7. Access the [Huzzah Get Started](https://azure.microsoft.com/en-us/documentation/samples/iot-hub-c-huzzah-getstartedkit/) tutorial to learn more about Microsoft Huzzah Dev Kit.


### Adafruit Feather M0
1. Install Feather M0 board support into your Arduino IDE.
    * Start Arduino and open Preferences window.
    * Enter `https://adafruit.github.io/arduino-board-index/package_adafruit_index.json` into Additional Board Manager URLs field. You can add multiple URLs, separating them with commas.
    * Open Boards Manager from Tools > Board menu and install `Arduino SAMD Boards` and `Adafruit SAMD Boards` 1.0.7 or later.
    * Select your `Adafruit Feather M0` from Tools > Board menu after installation
2. Install the `WiFi101` library from the Arduino IDE Library Manager.
3. Install the `RTCZero` library from the Arduino IDE Library Manager.
5. Open the `simplesample_http` example from the Arduino IDE File->AzureIoTHub->M0->Examples menu.
4. Update Wifi SSID/Password and IoT Hub Connection string in iot_configs.h
    * Ensure you are using a wifi network that does not require additional manual steps after connection, such as opening a web browser.
9. Access the [Feather M0 WiFi Get Started](https://azure.microsoft.com/en-us/documentation/samples/iot-hub-c-m0wifi-getstartedkit/) tutorial to learn more about Microsoft Feather M0 WiFi Dev Kit.

## License

See [LICENSE](LICENSE) file.

[azure-certifiedforiot]:  http://azure.com/certifiedforiot
[Microsoft-Azure-Certified-Badge]: images/Microsoft-Azure-Certified-150x150.png (Microsoft Azure Certified)
