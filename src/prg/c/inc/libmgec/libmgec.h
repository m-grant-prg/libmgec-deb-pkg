/**
 * @file src/prg/c/inc/libmgec/libmgec.h
 *
 * Header file for the libmgec shared library.
 *
 * @author Copyright (C) 2015-2019, 2021-2023  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.1.1 ==== 24/11/2023_
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

__attribute__((const)) const char *libmgec_get_pkg_version(void);

__attribute__((const)) const char *libmgec_get_src_version(void);

void libmgec_print_pkg_version(void);

void libmgec_print_src_version(void);

END_C_DECLS

#endif /* ndef LIBMGEC_H */
