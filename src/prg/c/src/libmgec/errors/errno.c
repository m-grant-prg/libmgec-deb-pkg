/**
 * @file lib/src/prg/c/src/libmgec/errors/errno.c
 *
 * Defines mge error variables.
 *
 * Definition of mge_errno error descriptions and global error variables.
 *
 * @author Copyright (C) 2017-2018  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0
 *
 * @version _v1.0.5 ==== 31/01/2018_
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
 * 31/01/2018	MG	1.0.5	Add No such lock message.		*
 *									*
 ************************************************************************
 */


#include <sys/types.h>


/* Error variables. */
int mge_errno;	/**< Error number. */
int sav_errno;	/**< Used to store errno, gai_errno etc. */

/**
 * Global array of mge-errno descriptions.
 */
const char *errno_desc[] = {
		"Success.",
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
		"No such lock."
		};

/**
 * Size of the error description array.
 */
const size_t errno_desc_size = sizeof(errno_desc) / sizeof(errno_desc[0]);
