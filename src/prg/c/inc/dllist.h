/**
 * @file src/prg/c/inc/dllist.h
 *
 * Doubly linked list header file.
 *
 * Header file for doubly linked lists in the libmgec shared library.
 *
 * @author Copyright (C) 2016-2019, 2021, 2022  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.0.9 ==== 21/08/2022_
 */

/* **********************************************************************
 *									*
 * Changelog								*
 *									*
 * Date		Author	Version	Description				*
 *									*
 * 06/05/2016	MG	1.0.1	First release.				*
 * 16/07/2016	MG	1.0.2	Move towards kernel coding style.	*
 * 17/07/2016	MG	1.0.3	Remove function prototype comments.	*
 * 05/11/2017	MG	1.0.4	Add Doxygen comments.			*
 * 09/11/2017	MG	1.0.5	Add SPDX license tag.			*
 * 02/01/2018	MG	1.0.6	Move to new source directory structure.	*
 * 11/06/2019	MG	1.0.7	clang-format coding style changes.	*
 *				Extract find_prev and find_next from .c	*
 *				file and make static inline.		*
 * 03/12/2021	MG	1.0.8	Tighten SPDX tag.			*
 * 21/08/2022	MG	1.0.9	Rename of portability.h			*
 *				Add stddef.h for size_t.		*
 *									*
 ************************************************************************
 */

#ifndef DLLIST_H
#define DLLIST_H

#include <mge-portability.h>

#include <stddef.h>

BEGIN_C_DECLS

/** Doubly linked list node. */
struct dllistnode {
	void *object;		     /**< The object attached to the node. */
	struct dllistnode *prevnode; /**< The preceding node. */
	struct dllistnode *nextnode; /**< The subsequent node. */
};

struct dllistnode *add_dll_node(struct dllistnode *currentnode,
				const void *object, size_t objsize);

/**
 * Find and return the previous node.
 * @param currentnode The current node.
 * @return A pointer to the previous node in the list or NULL if no previous
 * node exists.
 */
static inline struct dllistnode *
find_prev_dll_node(struct dllistnode *currentnode)
{
	return currentnode->prevnode;
}

/**
 * Find and return the next node.
 * @param currentnode The current node.
 * @return A pointer to the next node in the list or NULL if no subsequent
 * node exists.
 */
static inline struct dllistnode *
find_next_dll_node(struct dllistnode *currentnode)
{
	return currentnode->nextnode;
}

struct dllistnode *free_dllist(struct dllistnode *currentnode);

END_C_DECLS

#endif /* ndef DLLIST_H */
