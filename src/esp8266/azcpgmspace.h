// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

/** @file azcpgmspace.h
*	@brief Function prototypes for pgmspace functions that need extern-ing to C
*
*	@details These fucntions are just wrappers around existing ones in pgmspace.h that
*    are not defined in a way to make them linkable from c libs.
*/
#if defined(ARDUINO_ARCH_ESP8266)
#ifndef _AZCPGMSPACE_H
#define _AZCPGMSPACE_H

#include <pgmspace.h>

#ifdef __cplusplus
extern "C" {
#endif
char* az_c_strncpy_P(char* dest, PGM_P src, size_t size);
size_t az_c_strlen_P(PGM_P s);
#ifdef __cplusplus
}
#endif

#endif // _AZCPGMSPACE_H

#endif // #if defined(ARDUINO_ARCH_ESP8266)