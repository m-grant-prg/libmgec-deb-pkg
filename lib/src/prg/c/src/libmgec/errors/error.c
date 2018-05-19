/**
 * @file lib/src/prg/c/src/libmgec/errors/error.c
 *
 * Functions handling mge_errno.
 *
 * Functions supporting the use of the mge_errno system.
 *
 * @author Copyright (C) 2017-2018  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0
 *
 * @version _v1.0.5 ==== 19/05/2018_
 */

/* **********************************************************************
 *									*
 * Changelog								*
 *									*
 * Date		Author	Version	Description				*
 *									*
 * 03/05/2017	MG	1.0.1	First release.				*
 * 04/11/2017	MG	1.0.2	Add Doxygen comments.			*
 * 09/11/2017	MG	1.0.3	Add SPDX license tag.			*
 * 02/01/2018	MG	1.0.4	Move to new source directory structure.	*
 * 19/05/2018	MG	1.0.5	Remove external declarations to		*
 *				non-public internal.h header file.	*
 *									*
 ************************************************************************
 */


#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>

#include <mge-errno.h>
#include "internal.h"


static char err_msg[80];	/**< Storage for 'unknown error' string. */


/**
 * Return a string describing the error number.
 * If necessary look to errno, gai_errno etc.
 * @param mge_err The error number to look up.
 * @return The error message.
 */
const char *mge_strerror(const int mge_err)
{
	if ((mge_err > (int) errno_desc_size) || (mge_err < 0)) {
		sprintf(err_msg, "Unknown error %i", mge_err);
		return err_msg;
	}

	if (mge_err == MGE_ERRNO)
		return strerror(sav_errno);
	else if (mge_err == MGE_GAI)
		return gai_strerror(sav_errno);
	else
		return errno_desc[mge_err];
}
