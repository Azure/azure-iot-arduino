#ifndef AZUREIOTHUBCLIENT_H
#define AZUREIOTHUBCLIENT_H

#ifdef __cplusplus

#include <Client.h>

class AzureIoTHubClient
{
public:
    AzureIoTHubClient(Client& sslClient);

    void begin();
    void setEpochTime(unsigned long epochTime);

    static Client* sslClient;
};

#endif

#endif
