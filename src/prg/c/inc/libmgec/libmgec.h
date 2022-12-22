/**
 * @file src/prg/c/inc/libmgec/libmgec.h
 *
 * Header file for the libmgec shared library.
 *
 * @author Copyright (C) 2015-2019, 2021, 2022  Mark Grant
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
 * 06/08/2015	MG	1.0.1	First release.				*
 * 05/11/2017	MG	1.0.2	Add Doxygen comments.			*
 * 09/11/2017	MG	1.0.3	Add SPDX license tag.			*
 * 02/01/2018	MG	1.0.4	Move to new source directory structure.	*
 * 08/06/2019	MG	1.0.5	clang-format coding style changes.	*
 * 03/12/2021	MG	1.0.6	Tighten SPDX tag.			*
 * 09/06/2022	MG	1.0.7	Move array size macro here from the	*
 *				internal header file.			*
 * 16/09/2022	MG	1.0.8	Rename of portability.h			*
 *									*
 ************************************************************************
 */

#ifndef LIBMGEC_H
#define LIBMGEC_H

#include <libmgec/mge-portability.h>

BEGIN_C_DECLS

/**
 * A simple macro to standardise on the preferred method of determining the size
 * of an array.
 */
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

char *libmgec_get_pkg_version(void);

char *libmgec_get_src_version(void);

void libmgec_print_pkg_version(void);

void libmgec_print_src_version(void);

END_C_DECLS

#endif /* ndef LIBMGEC_H */
