// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "Arduino.h"
#include "azure_c_shared_utility/xlogging.h"

/*Codes_SRS_THREADAPI_ARDUINO_21_001: [ The threadapi_arduino shall implement the method sleep defined by the `threadapi.h`. ]*/
#include "azure_c_shared_utility/threadapi.h"

/*Codes_SRS_THREADAPI_ARDUINO_21_002: [ The ThreadAPI_Sleep shall receive a time in milliseconds. ]*/
/*Codes_SRS_THREADAPI_ARDUINO_21_003: [ The ThreadAPI_Sleep shall stop the thread for the specified time. ]*/
void ThreadAPI_Sleep(unsigned int milliseconds)
{
    delay(milliseconds);
}

/*Codes_SRS_THREADAPI_ARDUINO_21_004: [ The Arduino do not support ThreadAPI_Create, it shall return THREADAPI_ERROR. ]*/
THREADAPI_RESULT ThreadAPI_Create(THREAD_HANDLE* threadHandle, THREAD_START_FUNC func, void* arg)
{
    LogError("Arduino do not support multi-thread function.");
    return THREADAPI_ERROR;
}

/*Codes_SRS_THREADAPI_ARDUINO_21_005: [ The Arduino do not support ThreadAPI_Join, it shall return THREADAPI_ERROR. ]*/
THREADAPI_RESULT ThreadAPI_Join(THREAD_HANDLE threadHandle, int* res)
{
    LogError("Arduino do not support multi-thread function.");
    return THREADAPI_ERROR;
}

/*Codes_SRS_THREADAPI_ARDUINO_21_006: [ The Arduino do not support ThreadAPI_Exit, it shall not do anything. ]*/
void ThreadAPI_Exit(int res)
{
    LogError("Arduino do not support multi-thread function.");
}
