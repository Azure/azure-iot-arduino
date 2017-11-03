// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

// Please Use Arduino IDE 1.6.8 or later.

#include "iot_configs.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <SPI.h>
#include <WiFi101.h>


#include "simplesample_http.h"
#include "NTPClient.h"

#include <AzureIoTHub.h>
#include <AzureIoTProtocol_HTTP.h>

#ifdef ARDUINO_SAMD_FEATHER_M0

// Optional LIPO battery monitoring
#define VBAT_ENABLED 1
#define VBAT_PIN    A7

#define WINC_CS   8
#define WINC_IRQ  7
#define WINC_RST  4
#define WINC_EN   2

#endif


static char ssid[] = IOT_CONFIG_WIFI_SSID;
static char pass[] = IOT_CONFIG_WIFI_PASSWORD;

int status = WL_IDLE_STATUS;
WiFiSSLClient sslClient;

void setup() {
    // The Feather M0 loses it's COMn connection with every reset.
    // This 10 s delay allows you to reselect the COM port and open the serial monitor window.
    delay(10000);
    
    initSerial();

    #ifdef ARDUINO_SAMD_FEATHER_M0
    //Configure pins for Adafruit ATWINC1500 Feather
    Serial.println(F("WINC1500 on FeatherM0 detected."));
    Serial.println(F("Setting pins for WiFi101 library (WINC1500 on FeatherM0)"));
    WiFi.setPins(WINC_CS, WINC_IRQ, WINC_RST, WINC_EN);
    // for the Adafruit WINC1500 we need to enable the chip
    pinMode(WINC_EN, OUTPUT);
    digitalWrite(WINC_EN, HIGH);
    Serial.println(F("Enabled WINC1500 interface for FeatherM0"));
    #endif
    initWifi();
    
    initTime();
}

void loop() {
    simplesample_http_run();
}

void initSerial() {
    // Start serial and initialize stdout
    Serial.begin(115200);
    //Serial.setDebugOutput(true);
}

void initWifi() {
  // Attempt to connect to Wifi network:
    Serial.print("\r\n\r\nAttempting to connect to SSID: ");
    Serial.println(ssid);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\r\nConnected to wifi");
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void initTime() {
    WiFiUDP     _udp;

    time_t epochTime = (time_t)-1;

    NTPClient ntpClient;
    ntpClient.begin();

    while (true) {
        epochTime = ntpClient.getEpochTime("0.pool.ntp.org");

        if (epochTime == (time_t)-1) {
            Serial.println("Fetching NTP epoch time failed! Waiting 5 seconds to retry.");
            delay(5000);
        } else {
            Serial.print("Fetched NTP epoch time is: ");
            Serial.println(epochTime);
            break;
        }
    }
    
    ntpClient.end();

    struct timeval tv;
    tv.tv_sec = epochTime;
    tv.tv_usec = 0;

    settimeofday(&tv, NULL);
}



