#include "sdk/lock.h"

LOCK_HANDLE Lock_Init(void)
{
    return ((LOCK_HANDLE)NULL);
}

LOCK_RESULT Lock(LOCK_HANDLE  handle)
{
    return LOCK_ERROR;
}

LOCK_RESULT Unlock(LOCK_HANDLE  handle)
{
    return LOCK_ERROR;
}

LOCK_RESULT Lock_Deinit(LOCK_HANDLE  handle)
{
    return LOCK_ERROR;
}
