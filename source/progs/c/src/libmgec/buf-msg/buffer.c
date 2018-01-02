/**
 * @file lib/source/progs/c/src/libmgec/buf-msg/buffer.c
 *
 * Buffer processing functions.
 *
 * All buffer manipulation support functions.
 *
 * @author Copyright (C) 2017-2018  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0
 *
 * @version _v1.0.5 ==== 02/01/2018_
 */

/* **********************************************************************
 *									*
 * Changelog								*
 *									*
 * Date		Author	Version	Description				*
 *									*
 * 03/05/2017	MG	1.0.1	First release.				*
 * 04/11/2017	MG	1.0.2	Add Doxygen comments.			*
 * 09/11/2017	MG	1.0.3	Add SPDX license tag.			*
 * 21/11/2017	MG	1.0.4	Remove unnecessary initialisation of	*
 *				mge_errno.				*
 * 02/01/2018	MG	1.0.5	Move to new source directory structure.	*
 *									*
 ************************************************************************
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>

#include <mge-errno.h>
#include <mgebuffer.h>
#include <mgememory.h>


/**
 * Concatenate the used portion of a flat buffer into a buffer object.
 * On failure function arguments are unchanged and mge_errno will be set.
 * @param s_buf Source buffer.
 * @param s_buf_os Offset into source buffer ie extent of used portion.
 * @param m_buf The buffer object to use.
 * @return The processed buffer object. NULL on error.
 */
struct mgebuffer *concat_buf(const char *s_buf, const ssize_t s_buf_os,
	struct mgebuffer *m_buf)
{
	size_t t;
	int x = 0;
	char *m_buf_tmp;

	if (m_buf->buffer == NULL) {
		m_buf->buffer = mg_realloc(m_buf->buffer, m_buf->size);
		if (m_buf->buffer == NULL) {
			mge_errno = MGE_ERRNO;
			sav_errno = errno;
			return NULL;
		}
	}

	if ((m_buf->index + (int) s_buf_os) > (int) m_buf->size) {
		t = m_buf->size + (size_t) ((int) s_buf_os
			- ((int) m_buf->size - m_buf->index));
		m_buf_tmp = mg_realloc(m_buf->buffer, t);
		if (m_buf_tmp == NULL) {
			mge_errno = MGE_ERRNO;
			sav_errno = errno;
			return NULL;
		}
		m_buf->buffer = m_buf_tmp;
		m_buf->size = t;
	}
	while (x < s_buf_os)
		*(m_buf->buffer + (m_buf->index)++) = *(s_buf + x++);
	return m_buf;
}

/**
 * Remove processed data from a buffer object.
 * On failure function arguments are unchanged and mge_errno will be set.
 * @param m_buf Pointer to the buffer object to process.
 * @return Pointer to the processed buffer object or NULL on error.
 */
struct mgebuffer *trim_buf(struct mgebuffer *m_buf)
{
	char *t_buf = NULL;

	t_buf = mg_realloc(t_buf, (m_buf->size - m_buf->offset));
	if (t_buf == NULL) {
		mge_errno = MGE_ERRNO;
		sav_errno = errno;
		return NULL;
	}
	m_buf->size -= m_buf->offset;
	memcpy(t_buf, (m_buf->buffer + m_buf->offset), m_buf->size);
	free(m_buf->buffer);
	m_buf->buffer = t_buf;
	m_buf->index -= m_buf->offset;
	m_buf->offset = 0;
	return m_buf;
}

/**
 * Print a buffer object to stdout, (for debugging).
 * @param m_buf Buffer to print.
 */
void print_buf(struct mgebuffer *m_buf)
{
	printf("Print buffer struct:-\n");
	printf("\tEntire buffer:\t%.*s\n", m_buf->index, m_buf->buffer);
	printf("\tSize:\t\t%i\n", (int) m_buf->size);
	printf("\tOffset:\t\t%i\n", m_buf->offset);
	printf("\tIndex:\t\t%i\n", m_buf->index);
}
