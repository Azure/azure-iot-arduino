// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// Please use an Arduino IDE 1.6.8 or greater

// You must set the device id, device key, IoT Hub name and IotHub suffix in
// iot_configs.h
#include "iot_configs.h"

#include <AzureIoTHub.h>
#if defined(IOT_CONFIG_MQTT)
    #include <AzureIoTProtocol_MQTT.h>
#elif defined(IOT_CONFIG_HTTP)
    #include <AzureIoTProtocol_HTTP.h>
#endif

#include "sample.h"
#include "esp8266/sample_init.h"

static char ssid[] = IOT_CONFIG_WIFI_SSID;
static char pass[] = IOT_CONFIG_WIFI_PASSWORD;

void setup() {
    sample_init(ssid, pass);
}

// Azure IoT samples contain their own loops, so only run them once
static bool done = false;
void loop() {
    if (!done)
    {
        // Run the sample
        // You must set the device id, device key, IoT Hub name and IotHub suffix in
        // iot_configs.h
        sample_run();
        done = true;
    }
    else
    {
      delay(500);
    }
}

