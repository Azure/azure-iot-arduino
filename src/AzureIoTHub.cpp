// Copyright (c) Arduino. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <time.h>
#include <sys/time.h>

#if defined(ARDUINO_SAMD_FEATHER_M0)
#include <Adafruit_WINC1500.h>
#elif defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000)
#include <WiFi101.h>
#elif defined(ARDUINO_ARCH_ESP8266)
#include <ESP8266WiFi.h>
#else
#error "Unsupported platform"
#endif

#include "util/NTPClient.h"

#include "AzureIoTHub.h"

AzureIoTHubClass AzureIoTHub;

#if defined(ARDUINO_SAMD_FEATHER_M0)

#define WINC_CS   8
#define WINC_IRQ  7
#define WINC_RST  4
#define WINC_EN   2     // or, tie EN to VCC

Adafruit_WINC1500 WiFi(WINC_CS, WINC_IRQ, WINC_RST);
#endif

void AzureIoTHubClass::begin(const char ssid[], const char password[])
{
#if defined(ARDUINO_ARCH_ESP8266)
    Serial.setDebugOutput(true);
#endif

    setupWiFi(ssid, password);
    syncTime();
}

void AzureIoTHubClass::setupWiFi(const char ssid[], const char password[])
{
#if defined(ARDUINO_SAMD_FEATHER_M0) && defined(WINC_EN)
    pinMode(WINC_EN, OUTPUT);
    digitalWrite(WINC_EN, HIGH);
#endif

#if defined(ARDUINO_ARCH_SAMD)
    // check for the presence of the shield :
    if (WiFi.status() == WL_NO_SHIELD) {
        Serial.println("WiFi shield not present");
        // don't continue:
        while (true);
    }
#endif

    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    while (WiFi.begin(ssid, password) != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("Connected to wifi");
}

void AzureIoTHubClass::syncTime()
{
#if defined(ARDUINO_ARCH_SAMD)
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
#elif defined(ARDUINO_ARCH_ESP8266)
    time_t epochTime;

    configTime(0, 0, "pool.ntp.org", "time.nist.gov");

    while (true) {
        epochTime = time(NULL);

        if (epochTime == 0) {
            Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
            delay(2000);
        } else {
            Serial.print("Fetched NTP epoch time is: ");
            Serial.println(epochTime);
            break;
        }
    }
#endif
}
