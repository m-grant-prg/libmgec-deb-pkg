/**
 * @file src/prg/c/src/libmgec/errors/error.c
 *
 * Functions handling mge_errno.
 *
 * Functions supporting the use of the mge_errno system.
 *
 * @author Copyright (C) 2017-2019, 2021-2023  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.1.0 ==== 02/11/2023_
 */

#include <netdb.h>
#include <stdio.h>
#include <string.h>

#include "internal.h"
#include <libmgec/libmgec.h>
#include <libmgec/mge-errno.h>

static char err_msg[80]; /**< Storage for 'unknown error' string. */

/**
 * Return a string describing the error number.
 * If necessary look to errno, gai_errno etc.
 * @param mge_err The error number to look up.
 * @return The error message.
 */
const char *mge_strerror(const int mge_err)
{
	if ((mge_err > (int)errno_desc_size) || (mge_err < 0)) {
		snprintf(err_msg, ARRAY_SIZE(err_msg), "Unknown error %i",
			 mge_err);
		return err_msg;
	}

	if (mge_err == MGE_ERRNO)
		return strerror(sav_errno);
	else if (mge_err == MGE_GAI)
		return gai_strerror(sav_errno);
	else
		return errno_desc[mge_err];
}
