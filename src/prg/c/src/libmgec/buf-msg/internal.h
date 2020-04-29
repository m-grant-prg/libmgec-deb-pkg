/**
 * @file src/prg/c/src/libmgec/buf-msg/internal.h
 *
 * Non-public header file. No distribution required.
 *
 * @author Copyright (C) 2018, 2019-2020  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0
 *
 * @version _v1.0.3 ==== 29/04/2020_
 */

/* **********************************************************************
 *									*
 * Changelog								*
 *									*
 * Date		Author	Version	Description				*
 *									*
 * 09/09/2018	MG	1.0.1	First release.				*
 * 08/06/2019	MG	1.0.2	clang-format coding style changes.	*
 * 29/04/2020	MG	1.0.3	Add BUF_UNUSED_DEF_SIZE_MULT and	*
 *				BUF_MAX_UNREACH_PERCENT.		*
 *									*
 ************************************************************************
 */

#ifndef BUFMSG_INTERNAL_H
#define BUFMSG_INTERNAL_H

#include <portability.h>

BEGIN_C_DECLS

/**
 * Default buffer size.
 */
#define DEF_BUF_SIZE 256

/**
 * A multiple to be applied to the default buffer size and compared with the
 * amount of free space in the buffer to determine if shrinking is necessary.
 */
#define BUF_UNUSED_DEF_SIZE_MULT 3

/**
 * A percentage to be used for comparing the unreachable area of a buffer to the
 * buffer size to determine if the buffer requires compaction.
 * A sensible number is probably between 20 and 50.
 */
#define BUF_MAX_UNREACH_PERCENT 33

/**
 * Default message size.
 */
#define DEF_MSG_SIZE 256

END_C_DECLS

#endif /* ndef BUFMSG_INTERNAL_H */

