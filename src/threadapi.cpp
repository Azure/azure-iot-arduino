#include "Arduino.h"

#include "sdk/threadapi.h"

THREADAPI_RESULT ThreadAPI_Create(THREAD_HANDLE* threadHandle, THREAD_START_FUNC func, void* arg)
{
    return THREADAPI_INVALID_ARG;
}

THREADAPI_RESULT ThreadAPI_Join(THREAD_HANDLE threadHandle, int* res)
{
    return THREADAPI_INVALID_ARG;
}

void ThreadAPI_Exit(int res)
{
}

void ThreadAPI_Sleep(unsigned int milliseconds)
{
    delay(milliseconds);
}
