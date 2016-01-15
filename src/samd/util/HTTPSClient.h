// Copyright (c) Arduino. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <WiFi101.h>
#include <WiFiUdp.h>

#ifndef HTTPSCLIENT_H
#define HTTPSCLIENT_H

#define HTTPS_PORT          443

class HTTPSClient : public WiFiSSLClient
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
