/**
 * @file libmgec-lib/source/progs/c/src/libmgec/memory/memory.c
 *
 * Memory functions.
 *
 * All memory related support functions.
 *
 * @author Copyright (C) 2017  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0
 *
 * @version _v1.0.3 ==== 09/11/2017_
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
 *									*
 ************************************************************************
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>

#include <mge-errno.h>


/**
 * Wrap realloc to include error handling.
 * Also used for a malloc by passing mem_ptr as NULL.
 * On error mge_errno will be set and the old mem_ptr will be unchanged.
 * @param mem_ptr The memory area to be re-sized.
 * @param mem_sz The new size required.
 * @return the new memory area or NULL on error.
 */
char *mg_realloc(char *mem_ptr, const size_t mem_sz)
{
	mge_errno = 0;
	char *new_ptr = mem_ptr;

	new_ptr = realloc(mem_ptr, mem_sz);
	if (new_ptr == NULL) {
		mge_errno = MGE_ERRNO;
		sav_errno = errno;
		syslog((int) (LOG_USER | LOG_NOTICE), "ERROR on realloc - %s",
			strerror(sav_errno));
	}
	return new_ptr;
}
