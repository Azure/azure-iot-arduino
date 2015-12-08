// Copyright (c) Arduino. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "NTPClient.h"

#define LOCAL_UDP_PORT 2390

NTPClient::NTPClient() :
    _udp()
{
}

int NTPClient::begin()
{
    return _udp.begin(LOCAL_UDP_PORT);
}

uint32_t NTPClient::getEpochTime(const char* host, int port, unsigned long timeout)
{
    if (host == NULL || port < 1) {
        return (uint32_t)-1;
    }

    prepareRequest();
    sendRequest(host, port);

    if (!receiveResponse(timeout)) {
        return (uint32_t)-1;
    }

    return parseResponse();
}

void NTPClient::end()
{
    _udp.stop();
}

void NTPClient::prepareRequest()
{
    memset(_buffer, 0, NTP_PACKET_SIZE);

    // Initialize values needed to form NTP request
    _buffer[0] = 0b11100011;   // LI, Version, Mode
    _buffer[1] = 0;     // Stratum, or type of clock
    _buffer[2] = 6;     // Polling Interval
    _buffer[3] = 0xEC;  // Peer Clock Precision

    // 8 bytes of zero for Root Delay & Root Dispersion

    _buffer[12] = 49;
    _buffer[13] = 0x4E;
    _buffer[14] = 49;
    _buffer[15] = 52;
}

void NTPClient::sendRequest(const char* host, int port)
{
    _udp.beginPacket(host, port);
    _udp.write(_buffer, NTP_PACKET_SIZE);
    _udp.endPacket();
}

int NTPClient::receiveResponse(unsigned long timeout)
{
    long start = millis();
    int size = 0;

    while(size == 0 && (millis() - start) < timeout) {
        size = _udp.parsePacket();
    }

    if (size != NTP_PACKET_SIZE) {
        return 0;
    }

    _udp.read(_buffer, NTP_PACKET_SIZE);

    return 1;
}

uint32_t NTPClient::parseResponse()
{
    uint16_t high = word(_buffer[40], _buffer[41]);
    uint16_t low = word(_buffer[42], _buffer[43]);
    uint32_t ntpTime = high << 16 | low; // since 1900
    uint32_t epoch = ntpTime - 2208988800UL; // since 1970

    return epoch;
}
