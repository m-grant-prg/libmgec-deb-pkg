/**
 * @file src/prg/c/src/libmgec/buf-msg/message.c
 *
 * Message processing functions.
 *
 * All message handling support functions.
 *
 * @author Copyright (C) 2017-2023  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.1.0 ==== 02/11/2023_
 */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "internal.h"
#include <libmgec/libmgec.h>
#include <libmgec/mge-buffer.h>
#include <libmgec/mge-errno.h>
#include <libmgec/mge-memory.h>
#include <libmgec/mge-message.h>

/* @cond INTERNAL */
static struct mgemessage *get_msg(struct mgebuffer *buf,
				  struct mgemessage *msg);

static struct mgemessage *deconstruct_msg(struct mgemessage *msg);
/* @endcond */

/**
 * Number of arguments in the message.
 */
static int args;

/**
 * Pull a message from a buffer object.
 * @cond INTERNAL
 * Pull = Get, trim buffer and deconstruct.
 * @endcond
 * On error NULL is returned and mge_errno is set.
 * @param buf A buffer object.
 * @param msg A message object.
 * @return The resulting message object, partial or complete, or NULL on error.
 */
struct mgemessage *pull_msg(struct mgebuffer *buf, struct mgemessage *msg)
{
	struct mgebuffer *t_buf;
	struct mgemessage *t_msg;

	t_msg = get_msg(buf, msg);
	if (t_msg == NULL)
		return NULL;
	msg = t_msg;

	t_buf = trim_buf(buf);
	if (t_buf == NULL)
		return NULL;

	if (!msg->complete)
		return msg;

	return deconstruct_msg(msg);
}

/**
 * @cond INTERNAL
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
static struct mgemessage *get_msg(struct mgebuffer *buf, struct mgemessage *msg)
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
	return msg;

t_err_free:
	free(t_msg);
	return NULL;
}
/* @endcond */

/**
 * @cond INTERNAL
 * Deconstruct a complete message to its individual elements.
 * mge_errno is set on error.
 * @param msg A message object to process. Must be a complete message.
 * @return The resulting message object. NULL on error.
 */
static struct mgemessage *deconstruct_msg(struct mgemessage *msg)
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

	snprintf(toks, ARRAY_SIZE(toks), "%c%c", msg->separator,
		 msg->terminator);
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
/* @endcond */

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

	*msg = (struct mgemessage)MGEMESSAGE_INIT(terminator, separator);
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

/**
 * Print default values to stdout, for debugging.
 */
void print_def_msg_values(void)
{
	printf("DEF_MSG_SIZE - %i\n", DEF_MSG_SIZE);
}
