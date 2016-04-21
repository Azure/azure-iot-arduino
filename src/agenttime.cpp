// Copyright (c) Arduino. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "time.h"

#include "sdk/agenttime.h"

#include <NTPClient.h>

NTPClient* ntpClient = NULL;

time_t get_time(time_t* p)
{
    time_t t = ntpClient->getEpochTime();

    if (p) {
        *p = t;
    }

    return t;
}

double get_difftime(time_t stopTime, time_t startTime)
{
    return difftime(stopTime, startTime);
}
