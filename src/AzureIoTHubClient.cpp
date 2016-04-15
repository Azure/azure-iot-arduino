// Copyright (c) Arduino. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <time.h>
#include <sys/time.h>

#include <AzureIoTHubClient.h>

Client* AzureIoTHubClient::sslClient = NULL;

AzureIoTHubClient::AzureIoTHubClient(Client& sslClient)
{
    AzureIoTHubClient::sslClient = &sslClient;
}

void AzureIoTHubClient::begin()
{
}

void AzureIoTHubClient::setEpochTime(unsigned long epochTime)
{
#ifndef ARDUINO_ARCH_ESP8266
    struct timeval tv;

    tv.tv_sec = epochTime;
    tv.tv_usec = 0;
    settimeofday(&tv, NULL);
#endif
}
