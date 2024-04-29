/**
 * @file src/prg/c/src/libmgec/errors/errno.c
 *
 * Defines mge error variables.
 *
 * Definition of mge_errno error descriptions and global error variables.
 *
 * @author Copyright (C) 2017-2023  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.1.0 ==== 02/11/2023_
 */

#include <stddef.h>

#include "internal.h"
#include <libmgec/libmgec.h>
#include <libmgec/mge-errno.h>

/* Error variables. */
int mge_errno; /**< Error number. */
int sav_errno; /**< Used to store errno, gai_errno etc. */

/**
 * Global array of mge-errno descriptions.
 */
const char *errno_desc[] = { "Success.",
			     "sav_errno contains the errno error.",
			     "sav_errno contains the getaddrinfo error.",
			     "Bind or Connect failed on getaddrinfo data.",
			     "Error in parameters passed.",
			     "Duplicate node found.",
			     "Node not found.",
			     "Invalid config file parameter.",
			     "Cannot parse config file.",
			     "Invalid message received.",
			     "SSH error.",
			     "No such lock.",
			     "Client is blocked.",
			     "Identification error.",
			     "Protocol error.",
			     "General error" };

/**
 * Size of the error description array.
 */
const size_t errno_desc_size = ARRAY_SIZE(errno_desc);
