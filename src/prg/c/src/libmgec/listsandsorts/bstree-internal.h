/**
 * @file src/prg/c/src/libmgec/listsandsorts/bstree-internal.h
 *
 * Non-public header file for binary search trees in the libmgec shared library.
 * No distribution required.
 *
 * @author Copyright (C) 2015-2019, 2021, 2022  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.0.11 ==== 03/09/2022_
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
 * 03/09/2022	MG	1.0.11	Rename of portability.h			*
 *				Rename of bstree.h			*
 *				Add stddef.h for size_t.		*
 *				Move static function declarations to .c	*
 *				file.
 *				Test tracing elements moved here as	*
 *				they are not part of the API.		*
 *									*
 ************************************************************************
 */

#ifndef BSTREE_INTERNAL_H
#define BSTREE_INTERNAL_H

#include <mge-bstree.h>
#include <mge-portability.h>

#include <stddef.h>

BEGIN_C_DECLS

/** Node coordinates for test tracing. */
struct bstobjcoord {
	void *object; /**< The object. */
	int count;    /**< The node counter. */
	int xdir;     /**< The x coordinate. */
	int ydir;     /**< The y coordinate. */
};

struct bstobjcoord *find_next_bst_node_trace(const struct bstree *tree,
					     struct bstobjcoord *searchobj);

END_C_DECLS

#endif /* ndef BSTREE_INTERNAL_H */
