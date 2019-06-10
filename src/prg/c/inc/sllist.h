/**
 * @file src/prg/c/inc/sllist.h
 *
 * Singly linked list header file.
 *
 * Header file for singly linked lists in the libmgec shared library.
 *
 * @author Copyright (C) 2016-2019  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0
 *
 * @version _v1.0.7 ==== 10/06/2019_
 */

/* **********************************************************************
 *									*
 * Changelog								*
 *									*
 * Date		Author	Version	Description				*
 *									*
 * 02/05/2016	MG	1.0.1	First release.				*
 * 16/07/2016	MG	1.0.2	Move towards kernel coding style.	*
 * 17/07/2016	MG	1.0.3	Remove function prototype comments.	*
 * 05/11/2017	MG	1.0.4	Add Doxygen comments.			*
 * 09/11/2017	MG	1.0.5	Add SPDX license tag.			*
 * 02/01/2018	MG	1.0.6	Move to new source directory structure.	*
 * 10/06/2019	MG	1.0.7	clang-format coding style changes.	*
 *				Extract find_next_sll_node from c file	*
 *				and make static inline.			*
 *				Add for_each_sll_node macro.		*
 *									*
 ************************************************************************
 */

#ifndef SLLIST_H
#define SLLIST_H

#include <portability.h>

BEGIN_C_DECLS

/** Singly linked list node. */
struct sllistnode {
	void *object;		     /**< Attached object. */
	struct sllistnode *nextnode; /**< The subsequent node. */
};

struct sllistnode *add_sll_node(struct sllistnode *currentnode,
				const void *object, size_t objsize);

/**
 * Find the next node in the list.
 * @param currentnode The current node.
 * @return A pointer to the next node found in the list, or NULL if no
 * subsequent node exists.
 */
static inline struct sllistnode *
find_next_sll_node(struct sllistnode *currentnode)
{
	return currentnode->nextnode;
}

/**
 * Iterate over the list.
 * @param focus The current node in focus.
 * @param head The head of the list.
 */
#define for_each_sll_node(focus, head) \
	for (focus = head; focus != NULL; focus = focus->nextnode)

struct sllistnode *free_sllist(struct sllistnode *currentnode);

END_C_DECLS

#endif /* ndef SLLIST_H */

