/**
 * @file src/prg/c/src/libmgec/buf-msg/internal.h
 *
 * Non-public header file. No distribution required.
 *
 * @author Copyright (C) 2018-2023  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.1.0 ==== 02/11/2023_
 */

#ifndef BUFMSG_INTERNAL_H
#define BUFMSG_INTERNAL_H

#include <libmgec/mge-portability.h>

BEGIN_C_DECLS

/**
 * Default buffer size.
 * If DEF_BUF_SIZE exists it came from the gcc command line.
 */
#ifndef DEF_BUF_SIZE
	#define DEF_BUF_SIZE 256
#endif

/**
 * A multiple to be applied to the default buffer size and compared with the
 * amount of free space in the buffer to determine if shrinking is necessary.
 * A sensible number is probably between 2 and 10.
 * If BUF_UNUSED_DEF_SIZE_MULT exists it came from the gcc CL.
 */
#ifndef BUF_UNUSED_DEF_SIZE_MULT
	#define BUF_UNUSED_DEF_SIZE_MULT 3
#endif

/**
 * A percentage to be used for comparing the unreachable area of a buffer to the
 * buffer size to determine if the buffer requires compaction.
 * A sensible number is probably between 20 and 50.
 * If BUF_MAX_UNREACH_PERCENT exists it came from the gcc CL.
 */
#ifndef BUF_MAX_UNREACH_PERCENT
	#define BUF_MAX_UNREACH_PERCENT 33
#endif

/**
 * Default message size.
 * If DEF_MSG_SIZE exists it came form the gcc CL.
 */
#ifndef DEF_MSG_SIZE
	#define DEF_MSG_SIZE 256
#endif

END_C_DECLS

#endif /* ndef BUFMSG_INTERNAL_H */
