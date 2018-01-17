/**
 * @file lib/src/prg/c/src/libmgec/buf-msg/message.c
 *
 * Message processing functions.
 *
 * All message handling support functions.
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
 * 03/05/2017	MG	1.0.1	First release.				*
 * 04/11/2017	MG	1.0.2	Add Doxygen comments.			*
 * 09/11/2017	MG	1.0.3	Add SPDX license tag.			*
 * 02/01/2018	MG	1.0.4	Move to new source directory structure.	*
 *									*
 ************************************************************************
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>

#include <mge-errno.h>
#include <mgebuffer.h>
#include <mgememory.h>
#include <mgemessage.h>

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

	msg = deconstruct_msg(msg);
	if (msg->message == NULL)
		return msg;
	buf = trim_buf(buf);
	return msg;
}

/**
 * Get a message from a buffer object.
 * A message, (terminated with the mgemessage.terminator), is retrieved if a
 * complete message exists in the buffer object.
 * (Ignore CR & LF which can be the result of testing with telnet.)
 * On failure function arguments are unchanged and mge_errno will be set.
 * @param buf A buffer object.
 * @param msg A message object.
 * @return The resulting message object or NULL on error.
 */
struct mgemessage *get_msg(struct mgebuffer *buf, struct mgemessage *msg)
{
	char *t_msg;
	int t_buf_offset = 0;
	args = 1;
	msg->size = DEF_MSG_SIZE;

	t_msg = mg_realloc(msg->message, msg->size);
	if (t_msg == NULL) {
		mge_errno = MGE_ERRNO;
		sav_errno = errno;
		return NULL;
	}
	msg->message = t_msg;
	*msg->message = '\0';

	while ((t_buf_offset < buf->index) && !msg->complete) {
		if (*(buf->buffer + t_buf_offset) == msg->terminator)
			msg->complete = 1;
		if (*(buf->buffer + t_buf_offset) == msg->separator)
			args++;
		/* -1 allows space for adding '\0' to end of message. */
		if (msg->offset == msg->size - 1) {
			msg->size += DEF_MSG_SIZE;
			t_msg = mg_realloc(msg->message, msg->size);
			if (t_msg == NULL) {
				mge_errno = MGE_ERRNO;
				sav_errno = errno;
				return NULL;
			}
			msg->message = t_msg;
		}
		if ((*(buf->buffer + t_buf_offset) != '\n')
			&& (*(buf->buffer + t_buf_offset) != '\r')) {
			*(msg->message + msg->offset)
					= *(buf->buffer + t_buf_offset);
			msg->offset++;
		}
		t_buf_offset++;
	}
	*(msg->message + msg->offset++) = '\0';

	if (!msg->complete)
		return msg;

	buf->offset = t_buf_offset;
	return msg;
}

/**
 * Deconstruct a message to its individual elements.
 * @param msg A message object to process.
 * @return The resulting message object.
 */
struct mgemessage *deconstruct_msg(struct mgemessage *msg)
{
	char *start_tok;
	char *nxt_tok;
	int x;
	char msg_tmp[strlen(msg->message) + 1];

	strcpy(msg_tmp, msg->message);
	start_tok = msg_tmp;

	msg->argv = malloc((size_t) (args * (int) sizeof(char *)));
	if (msg->argv == NULL) {
		mge_errno = MGE_ERRNO;
		sav_errno = errno;
		return NULL;
	}

	/* Get arguments. */
	nxt_tok = strtok(start_tok, ",;");
	while (nxt_tok) {
		x = strlen(nxt_tok) + 1;
		*(msg->argv + msg->argc) = mg_realloc(NULL, (size_t) (x));
		if (*(msg->argv + msg->argc) == NULL) {
			mge_errno = MGE_ERRNO;
			sav_errno = errno;
			return NULL;
		}
		memcpy(*(msg->argv + msg->argc), nxt_tok, x);
		(msg->argc)++;
		nxt_tok = strtok('\0', ",;");
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

	*msg = (struct mgemessage) { .message = NULL, .size = 0, .offset = 0,
		.complete = 0, .terminator = terminator, .separator = separator,
		.argc = 0, .argv = NULL };
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
	printf("\tSize:\t\t%i\n", (int) msg->size);
	printf("\tOffset:\t\t%i\n", msg->offset);
	printf("\tComplete:\t%i\n", msg->complete);
	printf("\tTerminator:\t%c\n", msg->terminator);
	printf("\tSeparator:\t%c\n", msg->separator);

	for (i = 0; i < msg->argc; i++)
		printf("\tArgument %i is %s\n", i, *(msg->argv + i));
}
