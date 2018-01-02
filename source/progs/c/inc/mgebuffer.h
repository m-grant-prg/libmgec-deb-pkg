/**
 * @file dev/source/progs/c/inc/mgebuffer.h
 *
 * Header file for buffer processing.
 *
 * All buffer manipulation related information.
 *
 * @author Copyright (C) 2017-2018  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0
 *
 * @version _v1.0.4 ==== 02/01/2018_
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
 *									*
 ************************************************************************
 */


#ifndef MGEBUFFER_H
#define MGEBUFFER_H


#include <portability.h>
#include <sys/types.h>

BEGIN_C_DECLS

/**
 * Default buffer size.
 */
#define DEF_BUF_SIZE 256

/**
 * A buffer object.
 */
struct mgebuffer {
	char *buffer;	/**< Buffer storage. */
	size_t size;	/**< Size of the buffer storage area. */
	int offset;	/**< Next buffer location for processing. */
	int index;	/**< Next free buffer location. */
};

struct mgebuffer *concat_buf(const char *s_buf, const ssize_t s_buf_os,
	struct mgebuffer *m_buf);

struct mgebuffer *trim_buf(struct mgebuffer *msg_buf);

void print_buf(struct mgebuffer *m_buf);

END_C_DECLS

#endif /* ndef MGEBUFFER_H */
