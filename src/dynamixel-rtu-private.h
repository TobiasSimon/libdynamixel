/*
 * Copyright (C) 2013 Alexander Krause <alexander.krause@ed-solutions.de>
 * 
 * Dynamixel library - a fork from libmodbus (http://libmodbus.org)
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef _DYNAMIXEL_RTU_PRIVATE_H_
#define _DYNAMIXEL_RTU_PRIVATE_H_

#ifndef _MSC_VER
#include <stdint.h>
#else
#include "stdint.h"
#endif

#if defined(_WIN32)
#include <windows.h>
#else
#include <termios.h>
#endif

#define _DYNAMIXEL_RTU_HEADER_LENGTH      2
#define _DYNAMIXEL_RTU_PRESET_REQ_LENGTH  5
#define _DYNAMIXEL_RTU_PRESET_RSP_LENGTH  5

#define _DYNAMIXEL_RTU_CHECKSUM_LENGTH    1

#if defined(_WIN32)
#define ENOTSUP WSAEOPNOTSUPP

/* WIN32: struct containing serial handle and a receive buffer */
#define PY_BUF_SIZE 512
struct win32_ser {
	/* File handle */
	HANDLE fd;
	/* Receive buffer */
	uint8_t buf[PY_BUF_SIZE];
	/* Received chars */
	DWORD n_bytes;
};
#endif /* _WIN32 */

typedef struct _dynamixel_rtu {
	/* Device: "/dev/ttyS0", "/dev/ttyUSB0" or "/dev/tty.USA19*" on Mac OS X for
	 * KeySpan USB<->Serial adapters this string had to be made bigger on OS X
	 * as the directory+file name was bigger than 19 bytes. Making it 67 bytes
	 * for now, but OS X does support 256 byte file names. May become a problem
	 * in the future.
	 */
#if defined(__APPLE_CC__)
	char device[64];
#else
	char device[64];
#endif
	/* Bauds: 9600, 19200, 57600, 115200, etc */
	uint32_t baud;
	/* Data bit */
	uint8_t data_bit;
	/* Stop bit */
	uint8_t stop_bit;
	/* Parity: 'N', 'O', 'E' */
	char parity;
#if defined(_WIN32)
	struct win32_ser w_ser;
	DCB old_dcb;
#else
	/* Save old termios settings */
	struct termios old_tios;
#endif
#if HAVE_DECL_TIOCSRS485
	uint8_t serial_mode;
#endif
} dynamixel_rtu_t;

#endif /* _DYNAMIXEL_RTU_PRIVATE_H_ */
