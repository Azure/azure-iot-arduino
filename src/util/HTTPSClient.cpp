// Copyright (c) Arduino. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "HTTPSClient.h"

// #define DEBUG_STREAM Serial

HTTPSClient::HTTPSClient() :
    _contentLength(0)
{
}

int HTTPSClient::begin(const char* host, int port)
{
    return connect(host, port);
}

int HTTPSClient::sendRequest(const char* method, const char* path)
{
    _contentLength = 0;

#ifdef DEBUG_STREAM
    DEBUG_STREAM.print(method);
    DEBUG_STREAM.print(F(" "));
    DEBUG_STREAM.print(path);
    DEBUG_STREAM.print(F(" "));
    DEBUG_STREAM.println(F("HTTP/1.1"));
#endif

    print(method);
    print(F(" "));
    print(path);
    print(F(" "));
    println(F("HTTP/1.1"));

    return connected();
}

int HTTPSClient::sendHeader(const String& header)
{
#ifdef DEBUG_STREAM
    DEBUG_STREAM.println(header);
#endif

    println(header);

    return connected();
}

int HTTPSClient::sendBody(const unsigned char *content, int length)
{
#ifdef DEBUG_STREAM
    DEBUG_STREAM.println();
#endif

    println();

    if (length) {
#ifdef DEBUG_STREAM
        DEBUG_STREAM.write(content, length);
#endif
        write(content, length);
    }

    return connected();
}

int HTTPSClient::readStatus()
{
    int statusCode = -1;
    
    String status = readLine();
    status.trim();

#ifdef DEBUG_STREAM
    DEBUG_STREAM.println(status);
#endif

    int firstSpaceIndex = status.indexOf(' ');
    int lastSpaceIndex = status.lastIndexOf(' ');

    if (firstSpaceIndex == -1 || lastSpaceIndex == -1 || firstSpaceIndex == lastSpaceIndex) {
        return -1;
    }

    statusCode = status.substring(firstSpaceIndex + 1, lastSpaceIndex).toInt();

    if (statusCode == 0) {
        // bad parse
        statusCode = -1;
    }

    return statusCode;
}

int HTTPSClient::readHeader(String& name, String& value)
{
    String headerLine = readLine();
    headerLine.trim();

#ifdef DEBUG_STREAM
    DEBUG_STREAM.println(headerLine);
#endif

    if (headerLine.length() == 0) {
        return 0;
    }

    int colonIndex = headerLine.indexOf(':');

    if (colonIndex == -1) {
        return -1;
    }

    name = headerLine.substring(0, colonIndex);
    value = headerLine.substring(colonIndex + 1);

    name.trim();
    value.trim();

    if (name.equals("Content-Length")) {
        _contentLength = value.toInt();
    }

    return 1;
}

void HTTPSClient::end()
{
    stop();
}

String HTTPSClient::readLine()
{
    return readStringUntil('\n');
}

size_t HTTPSClient::contentLength()
{
    return _contentLength;
}

int HTTPSClient::readBody(unsigned char *content, int length)
{
    readBytes(content, length);
#ifdef DEBUG_STREAM
    DEBUG_STREAM.write(content, length);
#endif
    return 1;
}
