// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef XLOGGING_H
#define XLOGGING_H
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef void(*LOGGER_LOG)(unsigned int options, char* format, ...);

#define LOG_LINE 0x01

#define LOG(logger, ...) if (logger != NULL) logger(__VA_ARGS__)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* XLOGGING_H */
