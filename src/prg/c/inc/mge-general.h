/**
 * @file src/prg/c/inc/mge-general.h
 *
 * Non-public general header file. No distribution required.
 *
 * @author Copyright (C) 2018, 2019  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0
 *
 * @version _v1.0.2 ==== 08/06/2019_
 */

/* **********************************************************************
 *									*
 * Changelog								*
 *									*
 * Date		Author	Version	Description				*
 *									*
 * 09/09/2018	MG	1.0.1	First release.				*
 * 08/06/2019	MG	1.0.2	clang-format coding style changes.	*
 *									*
 ************************************************************************
 */

#ifndef MGEGENERAL_H
#define MGEGENERAL_H

#include <portability.h>

BEGIN_C_DECLS

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

END_C_DECLS

#endif /* ndef MGEGENERAL_H */

