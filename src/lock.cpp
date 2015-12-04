// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

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
