/**
 * @file lib/src/prg/c/src/libmgec/buf-msg/buffer.c
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
 * @version _v1.0.7 ==== 04/08/2018_
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
 * 27/01/2018	MG	1.0.6	mg_realloc syslogs error, sets		*
 *				mge_errno and saves errno, so if it	*
 *				returns NULL then just return NULL.	*
 * 04/08/2018	MG	1.0.7	Use new buffer.offset field name of	*
 *				proc_next.				*
 *				Use new buffer.index field name of	*
 *				next_free.				*
 *				If the buffer is NULL allocate the	*
 *				default size.				*
 *				Convert mgebuffer.proc_next and 	*
 *				next_free to size_t.			*
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
	ssize_t x = 0;
	char *m_buf_tmp;

	if (m_buf->buffer == NULL) {
		m_buf->buffer = mg_realloc(m_buf->buffer, DEF_BUF_SIZE);
		if (m_buf->buffer == NULL)
			return NULL;
		m_buf->size = DEF_BUF_SIZE;
	}

	if ((m_buf->next_free + s_buf_os) > m_buf->size) {
		t = m_buf->size + (s_buf_os - (m_buf->size - m_buf->next_free));
		m_buf_tmp = mg_realloc(m_buf->buffer, t);
		if (m_buf_tmp == NULL)
			return NULL;

		m_buf->buffer = m_buf_tmp;
		m_buf->size = t;
	}
	while (x < s_buf_os)
		*(m_buf->buffer + (m_buf->next_free)++) = *(s_buf + x++);
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

	t_buf = mg_realloc(t_buf, (m_buf->size - m_buf->proc_next));
	if (t_buf == NULL)
		return NULL;

	m_buf->size -= m_buf->proc_next;
	memcpy(t_buf, (m_buf->buffer + m_buf->proc_next), m_buf->size);
	free(m_buf->buffer);
	m_buf->buffer = t_buf;
	m_buf->next_free -= m_buf->proc_next;
	m_buf->proc_next = 0;
	return m_buf;
}

/**
 * Print a buffer object to stdout, (for debugging).
 * @param m_buf Buffer to print.
 */
void print_buf(struct mgebuffer *m_buf)
{
	printf("Print buffer struct:-\n");
	printf("\tEntire buffer:\t%.*s\n", (int) m_buf->next_free,
		m_buf->buffer);
	printf("\tSize:\t\t%zu\n", m_buf->size);
	printf("\tproc_next:\t\t%zu\n", m_buf->proc_next);
	printf("\tnext_free:\t\t%zu\n", m_buf->next_free);
}
