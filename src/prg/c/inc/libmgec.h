/**
 * @file src/prg/c/inc/libmgec.h
 *
 * Header file for the libmgec shared library.
 *
 * @author Copyright (C) 2015-2019  Mark Grant
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
 * 06/08/2015	MG	1.0.1	First release.				*
 * 05/11/2017	MG	1.0.2	Add Doxygen comments.			*
 * 09/11/2017	MG	1.0.3	Add SPDX license tag.			*
 * 02/01/2018	MG	1.0.4	Move to new source directory structure.	*
 * 08/06/2019	MG	1.0.5	clang-format coding style changes.	*
 *									*
 ************************************************************************
 */

#ifndef LIBMGEC_H
#define LIBMGEC_H

#include <portability.h>

BEGIN_C_DECLS

char *libmgec_get_pkg_version(void);

char *libmgec_get_src_version(void);

void libmgec_print_pkg_version(void);

void libmgec_print_src_version(void);

END_C_DECLS

#endif /* ndef LIBMGEC_H */

