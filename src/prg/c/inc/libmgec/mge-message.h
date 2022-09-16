/**
 * @file src/prg/c/inc/libmgec/mge-message.h
 *
 * Header file for message processing.
 *
 * All message manipulation related information.
 *
 * @author Copyright (C) 2017-2022  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.0.13 ==== 16/09/2022_
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
 * 04/08/2018	MG	1.0.5	Change mgemessage.offset to next_free	*
 *				and make it size_t.			*
 *				Change mgemessage.complete to bool.	*
 * 06/09/2018	MG	1.0.6	Add mgemessage struct initialiser.	*
 * 09/09/2018	MG	1.0.7	Move default message size macro to	*
 *				internal header file as it should not	*
 *				be part of the API.			*
 * 31/05/2019	MG	1.0.8	Use standard GNU ifdeffery around use	*
 *				of AC_HEADER_STDBOOL.			*
 * 08/06/2019	MG	1.0.9	clang-format coding style changes.	*
 * 19/07/2020	MG	1.0.10	Remove get_msg() declaration, remove it	*
 *				from API.				*
 *				Remove deconstruct_msg() declaration,	*
 *				remove it from API.			*
 * 16/04/2021	MG	1.0.11	Add print_def_msg_values() prototype.	*
 * 03/12/2021	MG	1.0.12	Tighten SPDX tag.			*
 * 16/09/2022	MG	1.0.13	Rename of portability.h			*
 *				Rename mgebuffer.h			*
 *				Rename to standard format mge-message.h	*
 *				Remove stdbool ifdeffery.		*
 *									*
 ************************************************************************
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
