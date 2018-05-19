/**
 * @file lib/src/prg/c/src/libmgec/errors/internal.h
 *
 * Non-public errors header file. No distribution required.
 *
 * @author Copyright (C) 2018  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0
 *
 * @version _v1.0.1 ==== 19/05/2018_
 */

/* **********************************************************************
 *									*
 * Changelog								*
 *									*
 * Date		Author	Version	Description				*
 *									*
 * 19/05/2018	MG	1.0.1	First release.				*
 *									*
 ************************************************************************
 */


#include <portability.h>


BEGIN_C_DECLS


/* This semi-hides these global variables, (cf putting them in mge-error.h). */
extern const char *errno_desc[];
extern const size_t errno_desc_size;


END_C_DECLS
