/**
 * @file dev/source/progs/c/inc/mgemessage.h
 *
 * Header file for message processing.
 *
 * All message manipulation related information.
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
 * 04/11/2017	MG	1.0.2	Add Doxygen comments.			*
 * 09/11/2017	MG	1.0.3	Add SPDX license tag.			*
 * 02/01/2018	MG	1.0.4	Move to new source directory structure.	*
 *									*
 ************************************************************************
 */


#ifndef MGEMESSAGE_H
#define MGEMESSAGE_H


#include <portability.h>
#include <sys/types.h>

#include <mgebuffer.h>


BEGIN_C_DECLS

/**
 * Default message size.
 */
#define DEF_MSG_SIZE 256

/**
 * Message object.
 */
struct mgemessage {
	char *message;		/**< The message buffer. */
	size_t size;		/**< Size of message buffer. */
	int offset;		/**< Next free message location. */
	int complete;		/**< Is message a complete message. */
	char terminator;	/**< Message delimmitter. */
	char separator;		/**< Message element delimitter. */
	int argc;		/**< Number of arguments to the message. */
	char **argv;		/**< Message arguments. */
};

struct mgemessage *pull_msg(struct mgebuffer *buf, struct mgemessage *msg);

struct mgemessage *get_msg(struct mgebuffer *buf, struct mgemessage *msg);

struct mgemessage *deconstruct_msg(struct mgemessage *msg);

void clear_msg(struct mgemessage *msg, const char terminator,
	const char separator);

void print_msg(struct mgemessage *msg);

END_C_DECLS

#endif /* ndef MGEMESSAGE_H */
