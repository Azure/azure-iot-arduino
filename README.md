# AzureIoTHub - Azure IoT Hub library for Arduino

The Azure Iot library for Arduino is under review and will be re-released soon. 

In the meantime, for Arduino scenarios we recommend using the Embedded C SDK in one of the following Samples:

- [ESP8266 Arduino Sample](https://github.com/Azure/azure-sdk-for-c/tree/main/sdk/samples/iot/aziot_esp8266)
- [ESP32 Arduino Sample](https://github.com/Azure/azure-sdk-for-c/tree/main/sdk/samples/iot/aziot_esp32)
- [Realtek Ameba Sample](https://github.com/Azure/azure-sdk-for-c/tree/main/sdk/samples/iot/aziot_realtek_amebaD)



## ARDUINO NANO 33 IOT

#####  ARDUINO NANO 33 IOT board

1. Install Arduino Nano33 IoT board support into your Arduino IDE.
    
    - Open Boards Manager from Tools > Board menu and install arduino nano 33 iot platform 1.8.11 or later

    - Select your Arduino Nano 33 IoT board from Tools > Board menu after installation

2. Open the `iothub_ll_telemetry_sample` example from the Arduino IDE File->Examples->AzureIoTHub menu.

3. Update Wifi SSID/Password in `iot_configs.h`

- Ensure you are using a wifi network that does not require additional manual steps after connection, such as opening a web browser.

4. Update IoT Hub Connection string in `iot_configs.h`

5. Configure board library using the automation script and `python3`. If you choose this method you can skip step 6.
    - Clone or download this repo: `git clone https://github.com/Azure/azure-iot-pal-arduino.git` , navigate to the downloaded sub-folder: `cd azure-iot-pal-arduino/build_all/base-libraries/AzureIoTHub/src/scripts` , and check that the script `automate_board_config.py` exists in this location. If this folder or script cannot be located, download the script [directly](https://raw.githubusercontent.com/Azure/azure-iot-pal-arduino/master/build_all/base-libraries/AzureIoTHub/src/scripts/automate_board_config.py).
    - Run the script E.x.: `python3 automate_board_config.py` and select appropriate options.
    - Note: if you update or reinstall your board library in Arduino you will need to run this script again.

6. Navigate to where your arduino nano 33 iot board package is located, typically in `C:\Users\<your username>\AppData\Local\Arduino15\packages` on Windows and `~/.arduino15/packages/` on Linux

	- Navigate deeper in to `hardware/samd/<board package version>/` where the `platform.txt` file lives.
	
	- Copy the [`platform.local.txt`](https://github.com/Azure/azure-iot-arduino/blob/master/examples/iothub_ll_telemetry_sample/ArduinoNano33iot/platform.local.txt) file from the `ArduinoNano33iot` folder in the sample into the same folder as the `platform.txt`.
	
	- Alternatively, or for later versions of the Board Package, add the define `-DDONT_USE_UPLOADTOBLOB` to `build.extra_flags=` in `platform.txt` or a `platform.local.txt` that you create.
	
7. Run the sample.
	
## License

See [LICENSE](LICENSE) file.


[azure-certifiedforiot]:  http://azure.com/certifiedforiot

[Microsoft-Azure-Certified-Badge]: images/Microsoft-Azure-Certified-150x150.png (Microsoft Azure Certified)

Complete information for contributing to the Azure IoT Arduino libraries

can be found [here](https://github.com/Azure/azure-iot-pal-arduino).


This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/). For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.