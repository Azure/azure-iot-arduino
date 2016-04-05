// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef XIO_H
#define XIO_H

#include "xlogging.h"

#ifdef __cplusplus
#include <cstddef>
extern "C" {
#else
#include <stddef.h>
#endif /* __cplusplus */

	typedef struct XIO_INSTANCE_TAG* XIO_HANDLE;
	typedef void* CONCRETE_IO_HANDLE;

	typedef enum IO_SEND_RESULT_TAG
	{
		IO_SEND_OK,
		IO_SEND_ERROR,
        IO_SEND_CANCELLED
	} IO_SEND_RESULT;

	typedef enum IO_OPEN_RESULT_TAG
	{
		IO_OPEN_OK,
		IO_OPEN_ERROR,
        IO_OPEN_CANCELLED
	} IO_OPEN_RESULT;

	typedef void(*ON_BYTES_RECEIVED)(void* context, const unsigned char* buffer, size_t size);
	typedef void(*ON_SEND_COMPLETE)(void* context, IO_SEND_RESULT send_result);
	typedef void(*ON_IO_OPEN_COMPLETE)(void* context, IO_OPEN_RESULT open_result);
	typedef void(*ON_IO_CLOSE_COMPLETE)(void* context);
	typedef void(*ON_IO_ERROR)(void* context);

	typedef CONCRETE_IO_HANDLE(*IO_CREATE)(void* io_create_parameters, LOGGER_LOG logger_log);
	typedef void(*IO_DESTROY)(CONCRETE_IO_HANDLE concrete_io);
	typedef int(*IO_OPEN)(CONCRETE_IO_HANDLE concrete_io, ON_IO_OPEN_COMPLETE on_io_open_complete, ON_BYTES_RECEIVED on_bytes_received, ON_IO_ERROR on_io_error, void* callback_context);
	typedef int(*IO_CLOSE)(CONCRETE_IO_HANDLE concrete_io, ON_IO_CLOSE_COMPLETE on_io_close_complete, void* callback_context);
	typedef int(*IO_SEND)(CONCRETE_IO_HANDLE concrete_io, const void* buffer, size_t size, ON_SEND_COMPLETE on_send_complete, void* callback_context);
	typedef void(*IO_DOWORK)(CONCRETE_IO_HANDLE concrete_io);

	typedef struct IO_INTERFACE_DESCRIPTION_TAG
	{
		IO_CREATE concrete_io_create;
		IO_DESTROY concrete_io_destroy;
		IO_OPEN concrete_io_open;
		IO_CLOSE concrete_io_close;
		IO_SEND concrete_io_send;
		IO_DOWORK concrete_io_dowork;
	} IO_INTERFACE_DESCRIPTION;

	extern XIO_HANDLE xio_create(const IO_INTERFACE_DESCRIPTION* io_interface_description, const void* io_create_parameters, LOGGER_LOG logger_log);
	extern void xio_destroy(XIO_HANDLE xio);
	extern int xio_open(XIO_HANDLE xio, ON_IO_OPEN_COMPLETE on_io_open_complete, ON_BYTES_RECEIVED on_bytes_received, ON_IO_ERROR on_io_error, void* callback_context);
	extern int xio_close(XIO_HANDLE xio, ON_IO_CLOSE_COMPLETE on_io_close_complete, void* callback_context);
	extern int xio_send(XIO_HANDLE xio, const void* buffer, size_t size, ON_SEND_COMPLETE on_send_complete, void* callback_context);
	extern void xio_dowork(XIO_HANDLE xio);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* XIO_H */
