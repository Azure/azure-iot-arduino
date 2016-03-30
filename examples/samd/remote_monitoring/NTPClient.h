// Copyright (c) Arduino. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifdef ARDUINO_SAMD_FEATHER_M0
#include <Adafruit_WINC1500.h>
#include <Adafruit_WINC1500Udp.h>
#elif defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000)
#include <WiFi101.h>
#include <WiFiUdp.h>
#endif

#ifndef NTPCLIENT_H
#define NTPCLIENT_H

#define NTP_PACKET_SIZE     48
#define NTP_PORT            123

#define DEFAULT_NTP_TIMEOUT 10000

class NTPClient
{
    public:
        NTPClient();
        int begin();
        uint32_t getEpochTime(const char* host, int port = NTP_PORT, unsigned long timeout = DEFAULT_NTP_TIMEOUT);
        void end();

    private:
        void prepareRequest();
        void sendRequest(const char* host, int port);
        int receiveResponse(unsigned long timeout);
        uint32_t parseResponse();

        char        _buffer[NTP_PACKET_SIZE];
#ifdef ARDUINO_SAMD_FEATHER_M0
        Adafruit_WINC1500UDP     _udp;
#elif defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000)
        WiFiUDP     _udp;
#endif

};

#endif
