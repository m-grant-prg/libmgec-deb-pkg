/**
 * @file src/prg/c/inc/libmgec/mge-memory.h
 *
 * Header file for memory functions.
 *
 * All memory manipulation related information.
 *
 * @author Copyright (C) 2017-2019, 2021-2023  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.1.0 ==== 02/11/2023_
 */

#ifndef MGE_MEMORY_H
#define MGE_MEMORY_H

#include <libmgec/mge-portability.h>

#include <sys/types.h>

BEGIN_C_DECLS

char *mg_realloc(char *mem_ptr, const size_t mem_sz);

END_C_DECLS

#endif /* ndef MGE_MEMORY_H */
