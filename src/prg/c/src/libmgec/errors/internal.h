/**
 * @file src/prg/c/src/libmgec/errors/internal.h
 *
 * Non-public errors header file. No distribution required.
 *
 * @author Copyright (C) 2018, 2019, 2021  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.0.4 ==== 03/12/2021_
 */

/* **********************************************************************
 *									*
 * Changelog								*
 *									*
 * Date		Author	Version	Description				*
 *									*
 * 19/05/2018	MG	1.0.1	First release.				*
 * 20/05/2018	MG	1.0.2	Add re-inclusion prevention #defines.	*
 * 08/06/2019	MG	1.0.3	clang-format coding style changes.	*
 * 03/12/2021	MG	1.0.4	Tighten SPDX tag.			*
 *									*
 ************************************************************************
 */

#ifndef ERRORS_INTERNAL_H
#define ERRORS_INTERNAL_H

#include <portability.h>

BEGIN_C_DECLS

/* This semi-hides these global variables, (cf putting them in mge-error.h). */
extern const char *errno_desc[];
extern const size_t errno_desc_size;

END_C_DECLS

#endif /* ndef ERRORS_INTERNAL_H */

