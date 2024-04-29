/**
 * @file src/prg/c/inc/libmgec/mge-buffer.h
 *
 * Header file for buffer processing.
 *
 * All buffer manipulation related information.
 *
 * @author Copyright (C) 2017-2019, 2021-2023  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.1.0 ==== 02/11/2023_
 */

#ifndef MGE_BUFFER_H
#define MGE_BUFFER_H

#include <libmgec/mge-portability.h>

#include <sys/types.h>

BEGIN_C_DECLS

/**
 * A buffer object.
 */
struct mgebuffer {
	char *buffer;	  /**< Buffer storage. */
	size_t size;	  /**< Size of the buffer storage area. */
	size_t proc_next; /**< Next buffer location for processing. */
	size_t next_free; /**< Next free buffer location. */
};

/**
 * A buffer object initialisation macro.
 */
#define MGEBUFFER_INIT                                                    \
	{                                                                 \
		.buffer = NULL, .size = 0, .proc_next = 0, .next_free = 0 \
	}

struct mgebuffer *concat_buf(const char *s_buf, const size_t s_buf_os,
			     struct mgebuffer *m_buf);

struct mgebuffer *trim_buf(struct mgebuffer *msg_buf);

void print_buf(struct mgebuffer *m_buf);

void print_def_buf_values(void);

END_C_DECLS

#endif /* ndef MGE_BUFFER_H */
