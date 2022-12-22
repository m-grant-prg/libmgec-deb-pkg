/**
 * @file src/prg/c/src/libmgec/listsandsorts/bstree-internal.h
 *
 * Non-public header file for binary search trees in the libmgec shared library.
 * No distribution required.
 *
 * @author Copyright (C) 2015-2019, 2021  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.0.10 ==== 03/12/2021_
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
 * 20/05/2018	MG	1.0.6	Standardise on define name format.	*
 * 02/06/2018	MG	1.0.7	Add support for counter and node totals	*
 *				for a tree.				*
 * 09/06/2019	MG	1.0.8	clang-format coding style changes.	*
 * 12/07/2019	MG	1.0.9	Separate combined header file into	*
 *				specific individual files.		*
 * 03/12/2021	MG	1.0.10	Tighten SPDX tag.			*
 *									*
 ************************************************************************
 */

#ifndef BSTREE_INTERNAL_H
#define BSTREE_INTERNAL_H

#include <portability.h>

#include <bstree.h>

BEGIN_C_DECLS

static struct bstreenode *add_node(struct bstreenode *currentnode,
				   const void *object, size_t objsize,
				   struct bstree *tree);

static void *find_node(const struct bstreenode *currentnode,
		       const void *searchobj,
		       int (*comp)(const void *, const void *));

static int get_counter_node(const struct bstreenode *currentnode,
			    const void *searchobj,
			    int (*comp)(const void *, const void *));

static void *find_next_node(const struct bstreenode *currentnode,
			    const void *searchobj,
			    int (*comp)(const void *, const void *));

static void *find_prev_node(const struct bstreenode *currentnode,
			    const void *searchobj,
			    int (*comp)(const void *, const void *));

static void *upd_node(struct bstreenode *currentnode, const void *updobj,
		      size_t objsize, int (*comp)(const void *, const void *));

static struct bstreenode *del_node(struct bstreenode *currentnode,
				   const void *searchobj, struct bstree *tree);

static struct bstreenode *free_bstree(struct bstreenode *currentnode);

static struct bstreenode *free_bst_node(struct bstreenode *currentnode);

static struct bstobjcoord *
find_next_node_trace(const struct bstreenode *currentnode,
		     struct bstobjcoord *searchobj,
		     int (*comp)(const void *, const void *));

END_C_DECLS

#endif /* ndef BSTREE_INTERNAL_H */

