// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "xio.h"

	extern int platform_init(void);
	extern void platform_deinit(void);
    extern const IO_INTERFACE_DESCRIPTION* platform_get_default_tlsio(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PLATFORM_H */
