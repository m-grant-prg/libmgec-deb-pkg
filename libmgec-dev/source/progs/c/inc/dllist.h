/**
 * @file libmgec-dev/source/progs/c/inc/dllist.h
 *
 * Doubly linked list header file.
 *
 * Header file for doubly linked lists in the libmgec shared library.
 *
 * @author Copyright (C) 2016-2017  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0
 *
 * @version _v1.0.5 ==== 09/11/2017_
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
 *									*
 ************************************************************************
 */


#ifndef DLLIST_H
#define DLLIST_H


#include <portability.h>

BEGIN_C_DECLS

/** Doubly linked list node. */
struct dllistnode {
	void *object;			/**< The object attached to the node. */
	struct dllistnode *prevnode;	/**< The preceding node. */
	struct dllistnode *nextnode;	/**< The subsequent node. */
};

struct dllistnode *add_dll_node(struct dllistnode *currentnode,
				const void *object, size_t objsize);

struct dllistnode *find_prev_dll_node(struct dllistnode *currentnode);

struct dllistnode *find_next_dll_node(struct dllistnode *currentnode);

struct dllistnode *free_dllist(struct dllistnode *currentnode);

END_C_DECLS

#endif /* ndef DLLIST_H */
