/**
 * @file src/prg/c/src/libmgec/errors/internal.h
 *
 * Non-public errors header file. No distribution required.
 *
 * @author Copyright (C) 2018, 2019, 2021-2023  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.1.0 ==== 02/11/2023_
 */

#ifndef ERRORS_INTERNAL_H
#define ERRORS_INTERNAL_H

#include <libmgec/mge-portability.h>

#include <stddef.h>

BEGIN_C_DECLS

/* This semi-hides these global variables, (cf putting them in mge-error.h). */
extern const char *errno_desc[];
extern const size_t errno_desc_size;

END_C_DECLS

#endif /* ndef ERRORS_INTERNAL_H */
