/**
 * @file src/prg/c/inc/mge-internal.h
 *
 * Non-public general header file. No distribution required.
 *
 * @author Copyright (C) 2018-2021  Mark Grant
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
 * 09/09/2018	MG	1.0.1	First release.				*
 * 08/06/2019	MG	1.0.2	clang-format coding style changes.	*
 * 29/06/2020	MG	1.0.3	Rename file to mge-internal.h so that	*
 *				it will be automatically excluded from	*
 *				API documentation.			*
 * 03/12/2021	MG	1.0.4	Tighten SPDX tag.			*
 *									*
 ************************************************************************
 */

#ifndef MGEINTERNAL_H
#define MGEINTERNAL_H

#include <portability.h>

BEGIN_C_DECLS

/**
 * A simple macro to standardise on the preferred method of determining the size
 * of an array.
 */
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

END_C_DECLS

#endif /* ndef MGEINTERNAL_H */

