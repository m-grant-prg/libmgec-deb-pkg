/**
 * @file src/prg/c/src/libmgec/memory/memory.c
 *
 * Memory functions.
 *
 * All memory related support functions.
 *
 * @author Copyright (C) 2017-2019, 2021-2023  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.1.0 ==== 02/11/2023_
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

#include <libmgec/mge-errno.h>
#include <libmgec/mge-memory.h>

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
	char *new_ptr = mem_ptr;

	mge_errno = 0;

	new_ptr = realloc(mem_ptr, mem_sz);
	if (new_ptr == NULL) {
		mge_errno = MGE_ERRNO;
		sav_errno = errno;
		syslog((int)(LOG_USER | LOG_NOTICE), "ERROR on realloc - %s",
		       strerror(sav_errno));
	}
	return new_ptr;
}
