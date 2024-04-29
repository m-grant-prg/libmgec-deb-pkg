/**
 * @file src/prg/c/inc/libmgec/sllist.h
 *
 * Singly linked list header file.
 *
 * Header file for singly linked lists in the libmgec shared library.
 *
 * @author Copyright (C) 2016-2019, 2021-2023  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.1.0 ==== 02/11/2023_
 */

#ifndef SLLIST_H
#define SLLIST_H

#include <libmgec/mge-portability.h>

#include <stddef.h>

BEGIN_C_DECLS

/** Singly linked list node. */
struct sllistnode {
	void *object;		 /**< Attached object. */
	struct sllistnode *next; /**< The subsequent node. */
};

struct sllistnode *add_head_sll_node(struct sllistnode *head,
				     const void *object, size_t objsize);

struct sllistnode *add_tail_sll_node(struct sllistnode *head,
				     const void *object, size_t objsize);

void *find_sll_node(struct sllistnode *head, const void *searchobj,
		    int (*comp)(const void *, const void *));

/**
 * Find the next node in the list.
 * @param focus The current node.
 * @return A pointer to the next node found in the list, or NULL if no
 * subsequent node exists.
 */
static inline struct sllistnode *find_next_sll_node(struct sllistnode *focus)
{
	return focus->next;
}

/**
 * Iterate over the list.
 * @param focus The current node in focus.
 * @param head The head of the list.
 */
#define for_each_sll_node(focus, head) \
	for (focus = head; focus != NULL; focus = focus->next)

struct sllistnode *free_sllist(struct sllistnode *head);

END_C_DECLS

#endif /* ndef SLLIST_H */
