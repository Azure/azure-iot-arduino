// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

/*Codes_SRS_PLATFORM_ARDUINO_21_001: [ The platform_arduino shall implement the interface provided in the `platfom.h`. ]*/
#include "azure_c_shared_utility/platform.h"
#include "tlsio_arduino.h"

/*Codes_SRS_PLATFORM_ARDUINO_21_003: [ The platform_init shall initialize the platform. ]*/
/*Codes_SRS_PLATFORM_ARDUINO_21_004: [ The platform_init shall allocate any memory needed to control the platform. ]*/
int platform_init(void)
{
    return 0;
}

/*Codes_SRS_PLATFORM_ARDUINO_21_005: [ The platform_deinit shall deinitialize the platform. ]*/
/*Codes_SRS_PLATFORM_ARDUINO_21_006: [ The platform_deinit shall free all allocate memory needed to control the platform. ]*/
void platform_deinit(void)
{

}

/*Codes_SRS_PLATFORM_ARDUINO_21_002: [ The platform_arduino shall use the tlsio functions defined by the 'xio.h'.*/
/*Codes_SRS_PLATFORM_ARDUINO_21_007: [ The platform_get_default_tlsio shall return a set of tlsio functions provided by the Arduino tlsio implementation. ]*/
const IO_INTERFACE_DESCRIPTION* platform_get_default_tlsio(void)
{
    return tlsio_arduino_get_interface_description();
}

