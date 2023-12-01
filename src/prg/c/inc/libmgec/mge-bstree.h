/**
 * @file src/prg/c/inc/libmgec/mge-bstree.h
 *
 * Binary search tree header file.
 *
 * Header file for binary search trees in the libmgec shared library.
 *
 * @author Copyright (C) 2015-2019, 2021-2023  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.1.0 ==== 02/11/2023_
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
