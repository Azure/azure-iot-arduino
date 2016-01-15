# AzureIoT - Azure IoT Hub library for Arduino

This library is a port of the [Microsoft Azure IoT device SDK for C](https://github.com/Azure/azure-iot-sdks/blob/master/c/readme.md) to Arduino. It allows you to use your Arduino/Genuino with the [Azure IoT Hub](https://azure.microsoft.com/en-us/services/iot-hub/).

Currently the library has been ported to ESP8266 and SAMD based boards:
- Atmel SAMD Based boards
  - Arduino/Genuino [MKR1000](https://www.arduino.cc/en/Main/ArduinoMKR1000) (untested)
  - Adafruit [Feather M0](https://www.adafruit.com/products/3010)
  - [Zero](https://www.arduino.cc/en/Main/ArduinoBoardZero) and [WiFi Shield 101](https://www.arduino.cc/en/Main/ArduinoWiFiShield101) 
- ESP8266 based boards with [esp8266/arduino](https://github.com/esp8266/arduino)
  - SparkFun [Thing](https://www.sparkfun.com/products/13711)
  - Adafruit [Feather Huzzah](https://www.adafruit.com/products/2821)

[![Microsoft Azure Certified][Microsoft-Azure-Certified-Badge]][azure-certifiedforiot]

## Getting started with MKR1000 or Zero

See the [Microsoft Azure IoT device SDK for C - Arduino WiFi Shield 101 and MKR1000 Setup Guide](https://github.com/Azure/azure-iot-sdks/blob/master/c/doc/run_sample_on_arduino_wifi101.md).

## Getting started with ESP8266

- Use Arduino IDE 1.6.8 or later (or [current hourly](https://www.arduino.cc/en/Main/Software) if not yet released).

- Install esp8266 board support from staging or from source at [esp8266/arduino](https://github.com/esp8266/arduino).

- Install this library from the Arduino IDE library manage, or from source:

```
cd C:\Program Files (x86)\Arduino\libraries
git clone <repo url for this source>
```
- Open sample provided in library directory 
```
\examples\esp8266\AzureIoTTest.ino
```
- Update Wifi SSID/Password in AzureIoTTest.ino
- Update Connection string in simplesample_http.c

## ESP8266 Tips
There is very little ram left available after the ESP SDK, SSL and Azure SDK.  Every effort must be made to store strings and data on flash rather than RAM.

There is no floating point printf support - you must use integer data types in your messages.

## License

See [LICENSE](LICENSE) file.

[azure-certifiedforiot]:  http://azure.com/certifiedforiot 
[Microsoft-Azure-Certified-Badge]: images/Microsoft-Azure-Certified-150x150.png (Microsoft Azure Certified)
