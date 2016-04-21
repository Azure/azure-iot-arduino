// Copyright (c) Arduino. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <AzureIoTHubClient.h>

extern HTTPSClient* httpsClient;
extern NTPClient* ntpClient;

AzureIoTHubClient::AzureIoTHubClient(Client& sslClient, UDP& ntpUdp):
    _httpsClient(sslClient),
    _ntpClient(ntpUdp)
{
    httpsClient = &_httpsClient;
    ntpClient = &_ntpClient;
}

void AzureIoTHubClient::begin()
{
  ntpClient->begin();

  while (!ntpClient->update()) {
    Serial.println("Fetching NTP epoch time failed! Waiting 5 seconds to retry.");
    delay(5000);
  }

  unsigned long epochTime = ntpClient->getEpochTime();

  Serial.print("Fetched NTP epoch time is: ");
  Serial.println(epochTime);
}
