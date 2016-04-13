///////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Attunix. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef _REM_CTRL_HTTP_H
#define _REM_CTRL_HTTP_H

#define MAX_CONNECTION_STRING_LEN (255)

#ifdef __cplusplus
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
// Param: Connection_string__cp  An ASCIIZ string containing a set of parameters including a URL
//                               and connection keys. i.e.
//                               "HostName=AuricIoTHubPiC.azure-devices.net;DeviceId=08578f25-777e-438b-876b-e2cfed911ab0;SharedAccessKey=Vg7u5edztBGW89KwHWvsHw=="
// Returns: true if string updated.
//          false if the string was too long (increase MAX_CONNECTION_STRING_LEN if you need to).
bool rem_ctrl_set_connection_string(const char * Connection_string__cp);

///////////////////////////////////////////////////////////////////////////////////////////////////
// Returns: 4 upon a successful initialization.
//          Values less than 4 indicate fewer successful steps during initialization.
int rem_ctrl_http_init(void);

///////////////////////////////////////////////////////////////////////////////////////////////////
// Cleanup. May not be needed for embedded applications.
void rem_ctrl_http_deinit(void);

///////////////////////////////////////////////////////////////////////////////////////////////////
// Call this when it's time to update the next sample in the outgoing stream.
void rem_ctrl_http_send_data(float Temp_c__f, float Pres_hPa__f, float Humi_pct__f);

///////////////////////////////////////////////////////////////////////////////////////////////////
// Call this about 10 times per second.
void rem_ctrl_http_run(void);

#ifdef __cplusplus
}
#endif

#endif//_REM_CTRL_HTTP_H

