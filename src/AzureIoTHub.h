// Copyright (c) Arduino. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef AZUREIOTHUB_H
#define AZUREIOTHUB_H

#include "sdk/lock.h"
#include "sdk/threadapi.h"
#include "sdk/serializer.h"

#include "sdk/iothub_client_ll.h"
#include "sdk/iothub_message.h"
#include "sdk/iothubtransporthttp.h"

#ifdef __cplusplus

class AzureIoTHubClass
{
public:
    void begin(const char ssid[], const char password[]);

private:
    void setupWiFi(const char ssid[], const char password[]);
    void syncTime();
};

extern AzureIoTHubClass AzureIoTHub;

#endif

#endif
