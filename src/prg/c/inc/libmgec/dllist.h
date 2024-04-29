/**
 * @file src/prg/c/inc/libmgec/dllist.h
 *
 * Doubly linked list header file.
 *
 * Header file for doubly linked lists in the libmgec shared library.
 *
 * @author Copyright (C) 2016-2019, 2021-2023  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.1.0 ==== 02/11/2023_
 */

#ifndef DLLIST_H
#define DLLIST_H

#include <libmgec/mge-portability.h>

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
