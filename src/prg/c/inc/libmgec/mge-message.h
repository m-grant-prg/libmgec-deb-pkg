/**
 * @file src/prg/c/inc/libmgec/mge-message.h
 *
 * Header file for message processing.
 *
 * All message manipulation related information.
 *
 * @author Copyright (C) 2017-2023  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.1.0 ==== 02/11/2023_
 */

#ifndef MGE_MESSAGE_H
#define MGE_MESSAGE_H

#include <stdbool.h>
#include <sys/types.h>

#include <libmgec/mge-buffer.h>
#include <libmgec/mge-portability.h>

BEGIN_C_DECLS

/**
 * Message object.
 */
struct mgemessage {
	char *message;	  /**< The message buffer. */
	size_t size;	  /**< Size of message buffer. */
	size_t next_free; /**< Next free message location. */
	bool complete;	  /**< Is message a complete message. */
	char terminator;  /**< Message delimmitter. */
	char separator;	  /**< Message element delimitter. */
	int argc;	  /**< Number of arguments to the message. */
	char **argv;	  /**< Message arguments. */
};

/**
 * mgemessage struct initialiser.
 */
#define MGEMESSAGE_INIT(a, b)                                                  \
	{                                                                      \
		.message = NULL, .size = 0, .next_free = 0, .complete = false, \
		.terminator = a, .separator = b, .argc = 0, .argv = NULL       \
	}

struct mgemessage *pull_msg(struct mgebuffer *buf, struct mgemessage *msg);

void clear_msg(struct mgemessage *msg, const char terminator,
	       const char separator);

void print_msg(struct mgemessage *msg);

void print_def_msg_values(void);

END_C_DECLS

#endif /* ndef MGE_MESSAGE_H */
