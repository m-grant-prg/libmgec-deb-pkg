/**
 * @file src/prg/c/src/libmgec/listsandsorts/internal.h
 *
 * Non-public header file for binary search trees in the libmgec shared library.
 * No distribution required.
 *
 * @author Copyright (C) 2015-2019, 2021-2023  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.1.0 ==== 02/11/2023_
 */

#ifndef INTERNAL_H
#define INTERNAL_H

#include <libmgec/mge-bstree.h>
#include <libmgec/mge-portability.h>

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

#endif /* ndef INTERNAL_H */
