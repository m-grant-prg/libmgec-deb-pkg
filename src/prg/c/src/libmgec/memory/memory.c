/**
 * @file src/prg/c/src/libmgec/memory/memory.c
 *
 * Memory functions.
 *
 * All memory related support functions.
 *
 * @author Copyright (C) 2017-2019, 2021, 2022  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.0.8 ==== 16/09/2022_
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
 * 27/03/2018	MG	1.0.5	Ensure variable declarations come	*
 *				before code, (fixes sparse warnings).	*
 *				Add mgememory.h for prototypes, (fixes	*
 *				sparse warning).			*
 * 09/06/2019	MG	1.0.6	clang-format coding style changes.	*
 * 03/12/2021	MG	1.0.7	Tighten SPDX tag.			*
 * 16/09/2022	MG	1.0.8	Rename mgememory.h			*
 *									*
 ************************************************************************
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
