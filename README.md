This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/). For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.

#### Azure IoT Hub Library source files


# AzureIoTHub - Azure IoT Hub library for Arduino

This is the location of the Arduino-specific source files for the

[AzureIoTHub Arduino published library](https://github.com/Azure/azure-iot-arduino). 

This library is a port of the [Microsoft Azure IoT device SDK for C](https://github.com/Azure/azure-iot-sdk-c) to Arduino. It allows you to use several Arduino compatible boards with Azure IoT Hub. Please submit any contribution directly to [azure-iot-sdks](https://github.com/Azure/azure-iot-sdks).

Currently supported hardware:

- ESP8266 based boards with [esp8266/arduino](https://github.com/esp8266/arduino)

  - SparkFun [Thing](https://www.sparkfun.com/products/13711)

  - Adafruit [Feather Huzzah](https://www.adafruit.com/products/2821)
  
- ESP32 based boards with [espressif/arduino-esp32](https://github.com/espressif/arduino-esp32)
  
  - Adafruit [HUZZAH32](https://www.adafruit.com/product/3405)

## Prerequisites

You should have the following ready before beginning with any board:

-   [Setup your IoT hub](https://github.com/Azure/azure-iot-device-ecosystem/blob/master/setup_iothub.md)

-   [Provision your device and get its credentials](https://github.com/Azure/azure-iot-device-ecosystem/blob/master/setup_iothub.md#create-new-device-in-the-iot-hub-device-identity-registry)

-   [Arduino IDE](https://www.arduino.cc/en/Main/Software)

-   Install the Azure IoT C SDK libraries by one of two options:
	1. Generate the Libraries by executing the [`make_sdk.py`](https://github.com/Azure/azure-iot-pal-arduino/blob/master/build_all/make_sdk.py) script within the `build_all` folder, E.x.: `python3 make_sdk.py -o <your-output-folder>`
	- Note: this is also currently the ONLY way to build the `AzureIoTSocket_WiFi` library for using the esp32.
	
	2. Install the following libraries through the Arduino IDE Library Manager:
	-   `AzureIoTHub`, `AzureIoTUtility`, `AzureIoTProtocol_MQTT`, `AzureIoTProtocol_HTTP`
	
# Simple Sample Instructions

## ESP8266

##### Sparkfun Thing, Adafruit Feather Huzzah, or generic ESP8266 board

1. Install esp8266 board support into your Arduino IDE.

    - Start Arduino and open Preferences window.

    - Enter `http://arduino.esp8266.com/stable/package_esp8266com_index.json` into Additional Board Manager URLs field. You can add multiple URLs, separating them with commas.

    - Open Boards Manager from Tools > Board menu and install esp8266 platform 2.5.2 or later

    - Select your ESP8266 board from Tools > Board menu after installation

2. Open the `iothub_ll_telemetry_sample` example from the Arduino IDE File->Examples->AzureIoTHub menu.

3. Update Wifi SSID/Password in `iot_configs.h`

    - Ensure you are using a wifi network that does not require additional manual steps after connection, such as opening a web browser.

4. Update IoT Hub Connection string in `iot_configs.h`

5. Configure board library using the automation script and `python3`. If you choose this method you can skip step 6.
    - Clone or download this repo: `git clone https://github.com/Azure/azure-iot-pal-arduino.git` , navigate to the downloaded sub-folder: `cd azure-iot-pal-arduino/build_all/base-libraries/AzureIoTHub/src/scripts` , and check that the script `automate_board_config.py` exists in this location. If this folder or script cannot be located, download the script [directly](https://raw.githubusercontent.com/Azure/azure-iot-pal-arduino/master/build_all/base-libraries/AzureIoTHub/src/scripts/automate_board_config.py).
    - Run the script E.x.: `python3 automate_board_config.py` and select appropriate options.
    - Note: if you update or reinstall your board library in Arduino you will need to run this script again.

6. Navigate to where your esp8266 board package is located, typically in `C:\Users\<your username>\AppData\Local\Arduino15\packages` on Windows and `~/.arduino15/packages/` on Linux
	
- Locate the board's `Arduino.h` (`hardware/esp8266/<board package version>/cores/esp8266/` and comment out the line containing `#define round(x)`, around line 137.

- Two folders up from the `Arduino.h` step above, in the same folder as the board's `platform.txt`, paste the [`platform.local.txt`](https://github.com/Azure/azure-iot-arduino/blob/master/examples/iothub_ll_telemetry_sample/esp8266/platform.local.txt) file from the `esp8266` folder in the sample into it.

	- Note1: It is necessary to add `-DDONT_USE_UPLOADTOBLOB` and `-DUSE_BALTIMORE_CERT` to `build.extra_flags=` in a `platform.txt` in order to run the sample, however, you can define them in your own `platform.txt` or a `platform.local.txt` of your own creation. 
	
	- Note2: If your device is not intended to connect to the global portal.azure.com, please change the CERT define to the appropriate cert define as laid out in [`certs.c`](https://github.com/Azure/azure-iot-sdk-c/blob/master/certs/certs.c)
	
	- Note3: Due to RAM limits, you must select just one CERT define.

7. Run the sample.
	
8. Access the [SparkFun Get Started](https://azure.microsoft.com/en-us/documentation/samples/iot-hub-c-thingdev-getstartedkit/) tutorial to learn more about Microsoft Sparkfun Dev Kit.

9. Access the [Huzzah Get Started](https://azure.microsoft.com/en-us/documentation/samples/iot-hub-c-huzzah-getstartedkit/) tutorial to learn more about Microsoft Huzzah Dev Kit.

## ESP32

##### Sparkfun ESP32 Thing, Adafruit ESP32 Feather, or generic ESP32 board

1. Install esp32 board support into your Arduino IDE.

    - Start Arduino and open Preferences window.

    - Enter `https://dl.espressif.com/dl/package_esp32_index.json` into Additional Board Manager URLs field. You can add multiple URLs, separating them with commas.

    - Open Boards Manager from Tools > Board menu and install esp32 platform 1.0.2 or later

    - Select your ESP32 board from Tools > Board menu after installation

2. Open the `iothub_ll_telemetry_sample` example from the Arduino IDE File->Examples->AzureIoTHub menu.

3. Update Wifi SSID/Password in `iot_configs.h`

- Ensure you are using a wifi network that does not require additional manual steps after connection, such as opening a web browser.

4. Update IoT Hub Connection string in `iot_configs.h`

5. Configure board library using the automation script and `python3`. If you choose this method you can skip step 6.
    - Clone or download this repo: `git clone https://github.com/Azure/azure-iot-pal-arduino.git` , navigate to the downloaded sub-folder: `cd azure-iot-pal-arduino/build_all/base-libraries/AzureIoTHub/src/scripts` , and check that the script `automate_board_config.py` exists in this location. If this folder or script cannot be located, download the script [directly](https://raw.githubusercontent.com/Azure/azure-iot-pal-arduino/master/build_all/base-libraries/AzureIoTHub/src/scripts/automate_board_config.py).
    - Run the script E.x.: `python3 automate_board_config.py` and select appropriate options.
    - Note: if you update or reinstall your board library in Arduino you will need to run this script again.

6. Navigate to where your esp32 board package is located, typically in `C:\Users\<your username>\AppData\Local\Arduino15\packages` on Windows and `~/.arduino15/packages/` on Linux

	- Navigate deeper in to `hardware/esp8266/<board package version>/` where the `platform.txt` file lives.
	
	- Copy the [`platform.local.txt`](https://github.com/Azure/azure-iot-arduino/blob/master/examples/iothub_ll_telemetry_sample/esp32/platform.local.txt) file from the `esp32` folder in the sample into the same folder as the `platform.txt`.
	
	- Alternatively, or for later versions of the Board Package, add the define `-DDONT_USE_UPLOADTOBLOB` to `build.extra_flags=` in `platform.txt` or a `platform.local.txt` that you create.
	
7. Run the sample.
	
8. Access the [SparkFun Get Started](https://azure.microsoft.com/en-us/documentation/samples/iot-hub-c-thingdev-getstartedkit/) tutorial to learn more about Microsoft Sparkfun Dev Kit.

9. Access the [Huzzah Get Started](https://azure.microsoft.com/en-us/documentation/samples/iot-hub-c-huzzah-getstartedkit/) tutorial to learn more about Microsoft Huzzah Dev Kit.

## License

See [LICENSE](LICENSE) file.


[azure-certifiedforiot]:  http://azure.com/certifiedforiot

[Microsoft-Azure-Certified-Badge]: images/Microsoft-Azure-Certified-150x150.png (Microsoft Azure Certified)

Complete information for contributing to the Azure IoT Arduino libraries

can be found [here](https://github.com/Azure/azure-iot-pal-arduino).
