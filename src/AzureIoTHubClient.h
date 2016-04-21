#ifndef AZUREIOTHUBCLIENT_H
#define AZUREIOTHUBCLIENT_H

#ifdef __cplusplus

#include <Client.h>
#include <Udp.h>

#include <NTPClient.h>

#include "util/HTTPSClient.h"

class AzureIoTHubClient
{
public:
    AzureIoTHubClient(Client& sslClient, UDP& ntpUdp);

    void begin();

private:
    HTTPSClient _httpsClient;
    NTPClient _ntpClient;
};

#endif

#endif
