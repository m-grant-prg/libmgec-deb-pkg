/**
 * @file src/prg/c/src/libmgec/buf-msg/message.c
 *
 * Message processing functions.
 *
 * All message handling support functions.
 *
 * @author Copyright (C) 2017-2020  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0
 *
 * @version _v1.0.13 ==== 29/03/2020_
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
 * 02/01/2018	MG	1.0.4	Move to new source directory structure.	*
 * 27/01/2018	MG	1.0.5	mg_realloc syslogs error, sets		*
 *				mge_errno and saves errno, so if it	*
 *				returns NULL then just return NULL.	*
 *				Preserve input parameters on error exit.*
 * 27/03/2018	MG	1.0.6	Use NULL not integer in strtok, (fixes	*
 *				sparse warning).			*
 * 19/05/2018	MG	1.0.7	Add args comment.			*
 * 17/06/2018	MG	1.0.8	get_msg now accommodates partial	*
 *				messages without re-processing the	*
 *				entire buffer. Data from the buffer	*
 *				extracted to the message struct could	*
 *				be a complete message, (terminated with	*
 *				the mgemessage.terminator), or a	*
 *				partial message. If it is an incomplete	*
 *				message then data will be appended to	*
 *				the partial message next time this	*
 *				function is invoked, repeating until a	*
 *				complete message is held in the struct.	*
 *				In deconstruct_msg replace hardcoded	*
 *				token string ",;" with message struct	*
 *				separator and terminator fields.	*
 * 04/08/2018	MG	1.0.9	Use new buffer.offset field name of	*
 *				proc_next.				*
 *				Use new buffer.index field name of	*
 *				next_free.				*
 *				Convert mgebuffer.proc_next to size_t.	*
 *				Convert mgemessage.offset to next_free	*
 *				and make it size_t.			*
 *				Change mgemessage.complete to bool.	*
 * 09/09/2018	MG	1.0.10	Include new internal.h			*
 * 08/05/2019	MG	1.0.11	x in deconstruct_msg is assigned by and	*
 *				used as a size_t so declare as such.	*
 * 08/06/2019	MG	1.0.12	clang-format coding style changes.	*
 * 29/03/2020	MG	1.0.13	Clarify message buffer capacity calc.	*
 *				Remove support for ignoring '\r' and	*
 *				'\n' in case debugging is in progress.	*
 *				Instead when using telnet for debugging	*
 *				- connect to host, go to telnet command	*
 *				prompt and enter mode character to	*
 *				communicate character by character with	*
 *				the server.				*
 *				Correctly ensure get_msg() returns	*
 *				unchanged arguments on error.		*
 *									*
 ************************************************************************
 */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

#include "internal.h"
#include <mge-errno.h>
#include <mgebuffer.h>
#include <mgememory.h>
#include <mgemessage.h>

/**
 * Number of arguments in the message.
 */
static int args;

/**
 * Pull a message from a buffer object.
 * Pull = Get, deconstruct and remove.
 * @param buf A buffer object.
 * @param msg A message object.
 * @return The resulting message object.
 */
struct mgemessage *pull_msg(struct mgebuffer *buf, struct mgemessage *msg)
{
	struct mgemessage *t_msg;

	t_msg = get_msg(buf, msg);
	if (t_msg == NULL)
		return NULL;
	msg = t_msg;

	if (!msg->complete)
		return msg;

	return deconstruct_msg(msg);
}

/**
 * Get a message from a buffer object.
 * Data from the buffer is extracted to the message struct. This could be a
 * complete message, (terminated with the mgemessage.terminator), or a partial
 * message. If it is an incomplete message then data will be appended to the
 * partial message next time this function is invoked, repeating until a
 * complete message is held in the struct. A complete message will have a NUL
 * appended to make future string processing easier.
 * On failure function arguments are unchanged and mge_errno will be set.
 * @param buf A buffer object.
 * @param msg A message object.
 * @return The resulting message object or NULL on error.
 */
struct mgemessage *get_msg(struct mgebuffer *buf, struct mgemessage *msg)
{
	size_t t_buf_proc_next = buf->proc_next;
	char *t_msg, *t1_msg;
	size_t t_msg_size, t_msg_next_free;
	bool t_msg_complete;

	/* Work on copies so args unchanged on error. */
	t_msg_size = msg->size;
	t_msg_next_free = msg->next_free;
	t_msg_complete = msg->complete;
	if (msg->message != NULL) {
		t_msg = malloc(t_msg_size);
		if (t_msg == NULL) {
			sav_errno = errno;
			mge_errno = MGE_ERRNO;
			return NULL;
		}
		t_msg = memcpy(t_msg, msg->message, t_msg_size);
	} else {
		t_msg = NULL;
	}

	/*
	 * Is this the first time processing this msg struct or is it a partial
	 * message.
	 */
	if (t_msg == NULL)
		args = 1;

	while ((t_buf_proc_next < buf->next_free) && !t_msg_complete) {
		if (*(buf->buffer + t_buf_proc_next) == msg->terminator)
			t_msg_complete = true;
		if (*(buf->buffer + t_buf_proc_next) == msg->separator)
			args++;
		/* +1 allow for EOM trailing NUL. */
		if (t_msg_next_free + 1 >= t_msg_size) {
			t_msg_size = t_msg_size + DEF_MSG_SIZE;
			t1_msg = mg_realloc(t_msg, t_msg_size);
			if (t1_msg == NULL)
				goto t_err_free;
			t_msg = t1_msg;
		}
		*(t_msg + t_msg_next_free) = *(buf->buffer + t_buf_proc_next);
		t_msg_next_free++;
		t_buf_proc_next++;
	}
	if (t_msg_complete)
		*(t_msg + t_msg_next_free) = '\0';

	buf->proc_next = t_buf_proc_next;
	msg->size = t_msg_size;
	msg->next_free = t_msg_next_free;
	msg->complete = t_msg_complete;
	free(msg->message);
	msg->message = t_msg;

	buf = trim_buf(buf);
	return msg;

t_err_free:
	free(t_msg);
	return NULL;
}

/**
 * Deconstruct a complete message to its individual elements.
 * mge_errno is set on error.
 * @param msg A message object to process. Must be a complete message.
 * @return The resulting message object. NULL on error.
 */
struct mgemessage *deconstruct_msg(struct mgemessage *msg)
{
	char *start_tok;
	char *nxt_tok;
	char toks[3];
	char msg_tmp[strlen(msg->message) + 1];
	size_t x;

	if (!msg->complete) {
		mge_errno = MGE_INVAL_MSG;
		return NULL;
	}

	sprintf(toks, "%c%c", msg->separator, msg->terminator);
	strcpy(msg_tmp, msg->message);
	start_tok = msg_tmp;

	msg->argv = malloc((size_t)(args * (int)sizeof(char *)));
	if (msg->argv == NULL) {
		mge_errno = MGE_ERRNO;
		sav_errno = errno;
		return NULL;
	}

	/* Get arguments. */
	nxt_tok = strtok(start_tok, toks);
	while (nxt_tok) {
		x = strlen(nxt_tok) + 1;
		*(msg->argv + msg->argc) = mg_realloc(NULL, x);
		if (*(msg->argv + msg->argc) == NULL)
			return NULL;

		memcpy(*(msg->argv + msg->argc), nxt_tok, x);
		(msg->argc)++;
		nxt_tok = strtok(NULL, toks);
	}
	return msg;
}

/**
 * Clear message struct.
 * Free memory allocated to the object and initialise the fields.
 * @param msg A message object to clear.
 * @param terminator The message delimitter to use.
 * @param separator The message element delimitter to use.
 */
void clear_msg(struct mgemessage *msg, const char terminator,
	       const char separator)
{
	int i;

	free(msg->message);
	for (i = 0; i < msg->argc; i++)
		free(*(msg->argv + i));
	free(msg->argv);

	*msg = (struct mgemessage){ .message = NULL,
				    .size = 0,
				    .next_free = 0,
				    .complete = false,
				    .terminator = terminator,
				    .separator = separator,
				    .argc = 0,
				    .argv = NULL };
}

/**
 * Print a message struct.
 * Useful for debugging.
 * @param msg The message object to print to stdout.
 */
void print_msg(struct mgemessage *msg)
{
	int i;

	printf("Print message struct:-\n");
	printf("\tEntire message:\t%s\n", msg->message);
	printf("\tSize:\t\t%i\n", (int)msg->size);
	printf("\tnext_free:\t\t%zu\n", msg->next_free);
	printf("\tComplete:\t%i\n", msg->complete);
	printf("\tTerminator:\t%c\n", msg->terminator);
	printf("\tSeparator:\t%c\n", msg->separator);

	for (i = 0; i < msg->argc; i++)
		printf("\tArgument %i is %s\n", i, *(msg->argv + i));
}

