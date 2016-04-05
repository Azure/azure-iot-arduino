// Copyright (c) Arduino. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <AzureIoTHub.h>

#include "simplesample_http.h"

char ssid[] = "yourNetwork"; //  your network SSID (name)
char pass[] = "secretPassword";    // your network password (use for WPA, or use as key for WEP)

void setup() {
    Serial.begin(9600);
    while(!Serial) {
        ;
    }

    AzureIoTHub.begin(ssid, pass);
}

void loop() {
    simplesample_http_run();
}

