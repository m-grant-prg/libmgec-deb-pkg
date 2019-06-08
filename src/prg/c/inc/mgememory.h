/**
 * @file src/prg/c/inc/mgememory.h
 *
 * Header file for memory functions.
 *
 * All memory manipulation related information.
 *
 * @author Copyright (C) 2017-2019  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0
 *
 * @version _v1.0.5 ==== 08/06/2019_
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
 * 02/01/2018	MG	1.0.4	Move to new source directory structure.	*
 * 08/06/2019	MG	1.0.5	clang-format coding style changes.	*
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

