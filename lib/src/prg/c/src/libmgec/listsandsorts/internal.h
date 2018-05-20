/**
 * @file lib/src/prg/c/src/libmgec/listsandsorts/internal.h
 *
 * Non-public header file for lists and sorts in the libmgec shared library.
 * No distribution required.
 *
 * @author Copyright (C) 2015-2018  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0
 *
 * @version _v1.0.5 ==== 20/05/2018_
 */

/* **********************************************************************
 *									*
 * Changelog								*
 *									*
 * Date		Author	Version	Description				*
 *									*
 * 04/11/2017	MG	1.0.1	Started ChangeLog.			*
 * 09/11/2017	MG	1.0.2	Add SPDX license tag.			*
 * 02/01/2018	MG	1.0.3	Move to new source directory structure.	*
 * 19/05/2018	MG	1.0.4	Include dllist and sllist prototypes.	*
 * 20/05/2018	MG	1.0.5	Add re-inclusion prevention #defines.	*
 *									*
 ************************************************************************
 */


#include <portability.h>


BEGIN_C_DECLS


#ifdef BSTREE_H

#ifndef INTERNAL_BSTREE_H
#define INTERNAL_BSTREE_H

static struct bstreenode *add_node(struct bstreenode *currentnode,
		const void *object, size_t objsize, int unique,
		int (*comp)(const void *, const void *));

static void *find_node(const struct bstreenode *currentnode,
		const void *searchobj, int (*comp)(const void *, const void *));

static int get_counter_node(const struct bstreenode *currentnode,
		const void *searchobj, int (*comp)(const void *, const void *));

static void *find_next_node(const struct bstreenode *currentnode,
		const void *searchobj, int (*comp)(const void *, const void *));

static void *find_prev_node(const struct bstreenode *currentnode,
		const void *searchobj, int (*comp)(const void *, const void *));

static void *upd_node(struct bstreenode *currentnode, const void *updobj,
		size_t objsize, int (*comp)(const void *, const void *));

static struct bstreenode *del_node(struct bstreenode *currentnode,
		const void *searchobj, int (*comp)(const void *, const void *));

static struct bstreenode *free_bstree(struct bstreenode *currentnode);

static struct bstreenode *free_bst_node(struct bstreenode *currentnode);

static struct bstobjcoord *find_next_node_trace(
		const struct bstreenode *currentnode,
		struct bstobjcoord *searchobj,
		int (*comp)(const void *, const void *));

#endif /* ifndef INTERNAL_BSTREE_H */
#endif /* ifdef BSTREE_H */


#ifdef DLLIST_H

#ifndef INTERNAL_DLLIST_H
#define INTERNAL_DLLIST_H

static void free_dll_node(struct dllistnode *currentnode);

#endif /* ifndef INTERNAL_DLLIST_H */
#endif /* ifdef DLLIST_H */


#ifdef SLLIST_H

#ifndef INTERNAL_SLLIST_H
#define INTERNAL_SLLIST_H

static void free_sll_node(struct sllistnode *currentnode);

#endif /* ifndef INTERNAL_SLLIST_H */
#endif /* ifdef SLLIST_H */


END_C_DECLS
