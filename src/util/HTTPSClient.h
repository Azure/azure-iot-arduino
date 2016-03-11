// Copyright (c) Arduino. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//

#ifdef ARDUINO_SAMD_FEATHER_M0
#include <Adafruit_WINC1500SSLClient.h>
#elif defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000)
#include <WifiSSLClient.h>
#elif defined(ESP8266)
#include <WiFiClientSecure.h>
#endif

#ifndef HTTPSCLIENT_H
#define HTTPSCLIENT_H

#define HTTPS_PORT          443

#ifdef ARDUINO_SAMD_FEATHER_M0
class HTTPSClient : public Adafruit_WINC1500SSLClient
#elif defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000)
class HTTPSClient : public WifiSSLClient
#elif defined(ESP8266)
class HTTPSClient : public WiFiClientSecure
#endif
{
    public:
        HTTPSClient();
        int begin(const char* host, int port = HTTPS_PORT);
        int sendRequest(const char* method, const char* path);
        int sendHeader(const String& header);
        int sendBody(const unsigned char *content, int length);
        int readStatus();
        int readHeader(String& name, String& value);
        size_t contentLength();
        int readBody(unsigned char *content, int length);
        void end();

    private:
        String readLine();

        size_t _contentLength;
};

#endif