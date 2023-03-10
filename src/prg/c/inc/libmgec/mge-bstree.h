/**
 * @file src/prg/c/inc/libmgec/mge-bstree.h
 *
 * Binary search tree header file.
 *
 * Header file for binary search trees in the libmgec shared library.
 *
 * @author Copyright (C) 2015-2019, 2021, 2022  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.0.14 ==== 16/09/2022_
 */

/* **********************************************************************
 *									*
 * Changelog								*
 *									*
 * Date		Author	Version	Description				*
 *									*
 * 05/11/2015	MG	1.0.1	First release.				*
 * 06/11/2015	MG	1.0.2	Elevate errno defs to listsandsorts.h.	*
 * 16/07/2016	MG	1.0.3	Move towards kernel coding style.	*
 * 17/07/2016	MG	1.0.4	Remove function prototype comments.	*
 * 21/01/2017	MG	1.0.5	listsandsorts.h mentioned above has	*
 *				been replaced with mgeerrno.h.		*
 * 22/03/2017	MG	1.0.6	Added node trace function prototype and	*
 *				struct.					*
 * 03/04/2017	MG	1.0.7	Add bst struct, cre_bst & del_bst()	*
 *				prototypes.				*
 * 04/11/2017	MG	1.0.8	Add Doxygen comments.			*
 * 09/11/2017	MG	1.0.9	Add SPDX license tag.			*
 * 02/01/2018	MG	1.0.10	Move to new source directory structure.	*
 * 02/06/2018	MG	1.0.11	Add node and counter totals to the tree	*
 *				struct.					*
 * 08/06/2019	MG	1.0.12	clang-format coding style changes.	*
 * 03/12/2021	MG	1.0.13	Tighten SPDX tag.			*
 * 16/09/2022	MG	1.0.14	New name for portability.h		*
 *				Rename to add namespace.		*
 *				Add stddef.h for size_t.		*
 *				Improve member comments.		*
 *				Move test tracing elements to internal	*
 *				header, they are not part of the API.	*
 *									*
 ************************************************************************
 */

#ifndef MGE_BSTREE_H
#define MGE_BSTREE_H

#include <libmgec/mge-portability.h>

#include <stddef.h>

BEGIN_C_DECLS

#define BST_NODES_UNIQUE 1     /**< BST allows unique nodes only. */
#define BST_NODES_DUPLICATES 0 /**< BST allows duplicate nodes. */

/** Binary search tree node. */
struct bstreenode {
	void *object;		      /**< The object attached to the node. */
	int count;		      /**< The node counter. If duplicates are
					allowed in the tree then this counter
					keeps track of the additions and
					deletions of this node. */
	struct bstreenode *childless; /**< Child node less than this node. */
	struct bstreenode *childgreater; /**< Child node greater than this
					   node. */
};

/** Binary search tree. */
struct bstree {
	struct bstreenode *root; /**< The root node of the tree. */
	int unique;		 /**< Uniqueness of nodes. Should be either
				   BST_NODES_UNIQUE or BST_NODES_DUPLICATES. */
	int count_total;	 /**< Sum of all node counters. */
	int node_total;		 /**< Number of nodes in the tree. */
	int (*comp)(const void *, const void *); /**< Comparison function. This
						   function must have the same
						   signature as strcmp() allbeit
						   with void parameters. */
};

struct bstree *cre_bst(int unique, int (*comp)(const void *, const void *));

struct bstree *add_bst_node(struct bstree *tree, const void *object,
			    size_t objsize);

void *find_bst_node(const struct bstree *tree, const void *searchobj);

int get_counter_bst_node(const struct bstree *tree, const void *searchobj);

void *find_next_bst_node(const struct bstree *tree, const void *searchobj);

void *find_prev_bst_node(const struct bstree *tree, const void *searchobj);

void *upd_bst_node(const struct bstree *tree, const void *updobj,
		   size_t objsize);

struct bstree *del_bst_node(struct bstree *tree, const void *searchobj);

struct bstree *del_bst(struct bstree *tree);

END_C_DECLS

#endif /* ndef MGE_BSTREE_H */
