/**
 * @file libmgec-dev/source/progs/c/inc/mgememory.h
 *
 * Header file for memory functions.
 *
 * All memory manipulation related information.
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
 * 24/10/2017	MG	1.0.1	This ChangeLog introduced.		*
 * 04/11/2017	MG	1.0.2	Add Doxygen comments.			*
 * 09/11/2017	MG	1.0.3	Add SPDX license tag.			*
 *									*
 ************************************************************************
 */


#ifndef MGEMEMORY_H
#define MGEMEMORY_H


#include <portability.h>
#include <sys/types.h>


BEGIN_C_DECLS

char *mg_realloc(char *mem_ptr, const size_t mem_sz);

END_C_DECLS

#endif /* ndef MGEMEMORY_H */
