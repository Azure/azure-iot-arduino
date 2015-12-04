#include <WiFi101.h>
#include <WiFiUdp.h>

#ifndef NTPCLIENT_H
#define NTPCLIENT_H

#define NTP_PACKET_SIZE     48
#define NTP_PORT            123

#define DEFAULT_NTP_TIMEOUT 1000

class NTPClient
{
    public:
        NTPClient();
        int begin();
        uint32_t getEpochTime(const char* host, int port = NTP_PORT, long timeout = DEFAULT_NTP_TIMEOUT);
        void end();

    private:
        void prepareRequest();
        void sendRequest(const char* host, int port);
        int receiveResponse(long timeout);
        uint32_t parseResponse();

        char        _buffer[NTP_PACKET_SIZE];
        WiFiUDP     _udp;
};

#endif
