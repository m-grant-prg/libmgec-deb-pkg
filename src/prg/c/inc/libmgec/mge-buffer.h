/**
 * @file src/prg/c/inc/libmgec/mge-buffer.h
 *
 * Header file for buffer processing.
 *
 * All buffer manipulation related information.
 *
 * @author Copyright (C) 2017-2019, 2021, 2022  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.0.12 ==== 12/09/2022_
 */

/* **********************************************************************
 *									*
 * Changelog								*
 *									*
 * Date		Author	Version	Description				*
 *									*
 * 24/10/2017	MG	1.0.1	This ChangeLog introduced.		*
 * 04/11/2017	MG	1.0.2	Add Doxygen commenting.			*
 * 09/11/2017	MG	1.0.3	Add SPDX license tag.			*
 * 02/01/2018	MG	1.0.4	Move to new source directory structure.	*
 * 04/08/2018	MG	1.0.5	Improve offset field name to proc_next.	*
 *				Improve index field name to next_free.	*
 *				Convert proc_next and next_free to	*
 *				size_t.					*
 * 06/09/2018	MG	1.0.6	Add an mgebuffer initialisation macro.	*
 * 09/09/2018	MG	1.0.7	Move default buffer size macro to	*
 *				internal header file as it should not	*
 *				be part of the API.			*
 * 25/05/2019	MG	1.0.8	Correct source buffer offset type to	*
 *				unsigned.				*
 * 08/06/2019	MG	1.0.9	clang-format coding style changes.	*
 * 15/04/2021	MG	1.0.10	Add print_def_buf_values() prototype.	*
 * 03/12/2021	MG	1.0.11	Tighten SPDX tag.			*
 * 12/09/2022	MG	1.0.12	Rename of portability.h			*
 *				Rename to standard format mge-buffer.h	*
 *				Use pkginclude location.		*
 *									*
 ************************************************************************
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
