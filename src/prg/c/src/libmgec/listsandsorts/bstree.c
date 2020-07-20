/**
 * @file src/prg/c/src/libmgec/listsandsorts/bstree.c
 *
 * Builds, searches and releases a binary search tree.
 *
 * This implementation supports object independence by using a comparison
 * function which conforms to the prototype:-\n
 *
 * > int (*comp)(const void *, const void *)
 *
 * and which returns the value of:-\n
 * > < 0 if the first parameter is less than the second,\n
 * > 0 if they are equal and\n
 * > \> 0 if the first is greater than the second.\n
 *
 * _In fact, the same as strcmp()._
 *
 * @author Copyright (C) 2015-2020  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0
 *
 * @version _v1.1.9 ==== 20/07/2020_
 */

/* **********************************************************************
 *									*
 * Changelog								*
 *									*
 * Date		Author	Version	Description				*
 *									*
 * 07/08/2015	MG	1.0.1	First release.				*
 * 11/08/2015	MG	1.0.2	Add functions delnode() & freenode().	*
 * 18/09/2015	MG	1.0.3	Change function names to XXX_bt_node().	*
 *				Change find_bt_node() to		*
 *				get_counter_bt_node() as it returns the	*
 *				count.					*
 *				Add find_bt_node(), upd_bt_node().	*
 *				Change free_btree() to return NULL.	*
 *				Add unique flag to add_bt_node().	*
 *				Improve overall use of btree_errno.	*
 *				Modify del_bt_node() to decrement the	*
 *				node counter instead of deleting the	*
 *				node if the counter is > 1, (i.e.	*
 *				duplicates are allowed).		*
 *				Add function parameter checking.	*
 *				Change defined flags and errors to be	*
 *				easily identifiable as btree elements.	*
 * 03/11/2015	MG	1.0.4	Change from bt and btree names to bst	*
 *				and bstree as this is a binary search	*
 *				tree, not a b-tree.			*
 * 11/11/2015	MG	1.0.5	Change for extraction of bstree.h from	*
 *				now umbrella listsandsorts.h.		*
 *				Add support for singly linked lists.	*
 *				Elevate errno defs to listsandsorts.h.	*
 *				Add base.c for common functions and	*
 *				definitions.				*
 * 16/07/2016	MG	1.0.6	Move towards kernel coding style.	*
 * 17/07/2016	MG	1.0.7	Further coding style change.		*
 * 12/03/2017	MG	1.0.8	get_counter_bst_node() now returns -1	*
 *				on error.				*
 * 03/05/2017	MG	1.1.0	Return NULL pointer, -1 or error number	*
 *				when possible on error.			*
 *				Apply coding standards from template	*
 *				atclstv v1.0.0				*
 *				Introduce library-wide mge_errno	*
 *				variable and error handling.		*
 *				Add bst trace function to provide node	*
 *				coordinates.				*
 *				Add exhaustive bstree tests.		*
 *				Introduce concept and support for a	*
 *				discreet bst object.			*
 * 04/11/2017	MG	1.1.1	Add Doxygen comments.			*
 * 09/11/2017	MG	1.1.2	Add SPDX license tag.			*
 * 02/01/2018	MG	1.1.3	Move to new source directory structure.	*
 * 27/03/2018	MG	1.1.4	Ensure variable declarations come	*
 *				before code, (fixes sparse warnings).	*
 * 12/05/2018	MG	1.1.5	Get_ functions now return -mge_errno	*
 *				instead of -1.				*
 * 02/06/2018	MG	1.1.6	Add counter and node totals for a tree.	*
 * 09/06/2019	MG	1.1.7	clang-format coding style changes.	*
 * 12/07/2019	MG	1.1.8	Change to specific internal header file.*
 * 20/07/2020	MG	1.1.9	Add internal-only documentation of	*
 *				static (non-API) function.		*
 *									*
 ************************************************************************
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bstree-internal.h"
#include <bstree.h>
#include <mge-errno.h>

/**
 * Create a binary search tree.
 * Creates a new binary search tree object which must eventually be freed by
 * del_bst().
 * On error mge_errno is set.
 * @param unique If set to true (1) then attempting to add a second identical
 * node will generate an error. If set to false (0) then adding identical nodes
 * increments the node counter.
 * @param comp A pointer to the comparison function to be used.
 * This implementation supports object independence by using a comparison
 * function which conforms to the prototype:-\n
 * > int (*comp)(const void *, const void *)
 * and which returns the value of:-\n
 * > < 0 if the first parameter is less than the second,\n
 * > 0 if they are equal and\n
 * > \> 0 if the first is greater than the second.\n
 * _In fact, the same as strcmp()._
 * @return A pointer to the newly created binary search tree or NULL on error.
 */
struct bstree *cre_bst(int unique, int (*comp)(const void *, const void *))
{
	struct bstree *newtree;

	if (comp == NULL) {
		mge_errno = MGE_PARAM;
		return NULL;
	}

	if ((unique != BST_NODES_UNIQUE) && (unique != BST_NODES_DUPLICATES)) {
		mge_errno = MGE_PARAM;
		return NULL;
	}

	newtree = malloc(sizeof(struct bstree));
	if (newtree == NULL) {
		mge_errno = MGE_ERRNO;
		sav_errno = errno;
		return NULL;
	}
	newtree->root = NULL;
	newtree->unique = unique;
	newtree->count_total = 0;
	newtree->node_total = 0;
	newtree->comp = comp;
	return newtree;
}

/**
 * Add a node to a binary search tree.
 * Attempts to add a node to a binary search tree. If the node exists and unique
 * is true for this tree, an error is generated, if unique is false then the
 * node counter is incremented.
 * On error mge_errno is set and NULL is returned but the bst will remain as
 * before the failed add. Hence it is important to preserve the pointer to the
 * tree across this function.\n
 *
 *     tmp_tree = add_bst_node(tree, object, objsize);
 *     if (tmp_tree == NULL) {
 *     		... error handling
 * 		return error;
 *     }
 *     tree = tmp_tree;
 *
 * @param tree The tree to add to.
 * @param object The object to add.
 * @param objsize The size of the object.
 * @return A pointer to the binary tree 'tree' or NULL on error.
 */
struct bstree *add_bst_node(struct bstree *tree, const void *object,
			    size_t objsize)
{
	struct bstreenode *addnode;

	addnode = add_node(tree->root, object, objsize, tree);
	if (addnode == NULL)
		return NULL;
	tree->root = addnode;
	return tree;
}

/**
 * @cond INTERNAL
 * Add a binary search tree node with data of 'object' and using object
 * comparison function of 'comp'. Node uniqueness is defined by the unique
 * parameter.
 * Errors - mge_errno will be set as required.
 * @param currentnode - On call from user code is a pointer to the root node or
 * NULL if tree not yet started. Within the function and in recursion it is the
 * node being processed.
 * @param object The object to add.
 * @param objsize The size of the object.
 * @param tree The tree to add to.
 * @return Returns NULL on error. On exit to user code a pointer to the root
 * node. Within the function it is a pointer to the node being processed. On
 * error the bst will remain as before the failed add. Hence it is important to
 * preserve the pointer to the root node across this function.
 */
static struct bstreenode *add_node(struct bstreenode *currentnode,
				   const void *object, size_t objsize,
				   struct bstree *tree)
{
	struct bstreenode *tmp_node;

	mge_errno = 0;

	if (object == NULL || !objsize || tree->comp == NULL) {
		mge_errno = MGE_PARAM;
		return NULL;
	}

	if (currentnode == NULL) {
		/* A new object */
		currentnode = malloc(sizeof(struct bstreenode));
		if (currentnode != NULL) {
			currentnode->object = malloc(objsize);
			if (currentnode->object != NULL) {
				/* Copy object and initialise node. */
				currentnode->object = memcpy(
					currentnode->object, object, objsize);
				currentnode->count = 1;
				currentnode->childless
					= currentnode->childgreater = NULL;
				tree->count_total++;
				tree->node_total++;
				return currentnode;
			} else {
				/* Cannot malloc object */
				mge_errno = MGE_ERRNO;
				sav_errno = errno;
				free(currentnode);
				return NULL;
			}
		} else {
			/* Cannot malloc node */
			mge_errno = MGE_ERRNO;
			sav_errno = errno;
			return NULL;
		}
	}

	if ((*(tree->comp))(object, currentnode->object) == 0) {
		/* Node exists */
		if (tree->unique) {
			mge_errno = MGE_DUPLICATE_NODE;
			return NULL;
		} else {
			(currentnode->count)++;
			tree->count_total++;
			return currentnode;
		}
	}

	if ((*(tree->comp))(object, currentnode->object) < 0) {
		/* Look lower */
		tmp_node = add_node(currentnode->childless, object, objsize,
				    tree);
		if (tmp_node != NULL) {
			currentnode->childless = tmp_node;
			return currentnode;
		} else {
			return NULL;
		}
	}

	if ((*(tree->comp))(object, currentnode->object) > 0) {
		/* Look higher */
		tmp_node = add_node(currentnode->childgreater, object, objsize,
				    tree);
		if (tmp_node != NULL) {
			currentnode->childgreater = tmp_node;
			return currentnode;
		} else {
			return NULL;
		}
	}
	return currentnode;
}
/* @endcond */

/**
 * Find an exact object match.
 * Find an exact object match in the bst 'tree'.
 * On error mge_errno will be set.
 * @param tree The bst to search.
 * @param searchobj The object to find. It does not need to be a fully
 * populated object. It only needs enough information to support the comparison
 * function. E.g. a key.
 * @return A pointer to the object found in the node, (i.e. the fully
 * populated object), or, NULL if not found or an error was encountered.
 */
void *find_bst_node(const struct bstree *tree, const void *searchobj)
{
	if (tree == NULL) {
		mge_errno = MGE_PARAM;
		return NULL;
	}
	return find_node(tree->root, searchobj, tree->comp);
}

/**
 * @cond INTERNAL
 * Find exact object match.
 * Errors - mge_errno will be set as required.
 * @param currentnode - On invocation from user code this is the root node.
 * @param searchobj - The object to find. It does not need to be a fully
 * populated object. It only needs enough information to support the comparison
 * function. E.g. a key.
 * @param comp A pointer to the comparison function to be used.
 * @return Returns a pointer to the object found in the node, (i.e. the fully
 * populated object), or, NULL if not found or an error was encountered.
 */
static void *find_node(const struct bstreenode *currentnode,
		       const void *searchobj,
		       int (*comp)(const void *, const void *))
{
	void *foundobj = NULL;

	mge_errno = 0;

	if (searchobj == NULL || comp == NULL) {
		mge_errno = MGE_PARAM;
		return NULL;
	}

	if (currentnode == NULL)
		return NULL;

	if ((*comp)(searchobj, currentnode->object) == 0) {
		foundobj = currentnode->object;
	} else if ((*comp)(searchobj, currentnode->object) < 0) {
		foundobj = find_node(currentnode->childless, searchobj, comp);
	} else if ((*comp)(searchobj, currentnode->object) > 0) {
		foundobj
			= find_node(currentnode->childgreater, searchobj, comp);
	}
	return foundobj;
}
/* @endcond */

/**
 * Get the counter for a node.
 * Get the node counter for an object in the bst 'tree'.
 * On error mge_errno will be set.
 * @param tree The bst to search.
 * @param searchobj The object to find. It does not need to be a fully
 * populated object. It only needs enough information to support the comparison
 * function. E.g. a key.
 * @return The number of times add_bst_node() was asked to create this node,
 * or, 0 if not found, or, -mge_errno on error.
 */
int get_counter_bst_node(const struct bstree *tree, const void *searchobj)
{
	if (tree == NULL) {
		mge_errno = MGE_PARAM;
		return -mge_errno;
	}
	return get_counter_node(tree->root, searchobj, tree->comp);
}

/**
 * @cond INTERNAL
 * Find exact object match. Returns the number of matches.
 * Errors - mge_errno will be set as required.
 * @param currentnode - On invocation from user code this is the root node.
 * @param searchobj - The object to find. It does not need to be a fully
 * populated object. It only needs enough information to support the comparison
 * function. E.g. a key.
 * @param comp A pointer to the comparison function to be used.
 * @return Returns the number of times add_bst_node() was asked to create this
 * node, or, 0 if not found, or, -mge_errno on error.
 */
static int get_counter_node(const struct bstreenode *currentnode,
			    const void *searchobj,
			    int (*comp)(const void *, const void *))
{
	int count = 0;

	mge_errno = 0;

	if (searchobj == NULL || comp == NULL) {
		mge_errno = MGE_PARAM;
		return -mge_errno;
	}

	if (currentnode == NULL)
		return 0;

	if ((*comp)(searchobj, currentnode->object) == 0) {
		count = currentnode->count;
	} else if ((*comp)(searchobj, currentnode->object) < 0) {
		count = get_counter_node(currentnode->childless, searchobj,
					 comp);
	} else if ((*comp)(searchobj, currentnode->object) > 0) {
		count = get_counter_node(currentnode->childgreater, searchobj,
					 comp);
	}
	return count;
}
/* @endcond */

/**
 * Find the next node.
 * Find the next node in the bst and return the object.
 * On error mge_errno will be set.
 * @param tree The bst to search.
 * @param searchobj The object to find. It does not need to be a fully
 * populated object. It only needs enough information to support the comparison
 * function. E.g. a key.
 * @return A pointer to the next object found in the tree, (i.e. a fully
 * populated object), or, NULL if not found or an error was encountered.
 */
void *find_next_bst_node(const struct bstree *tree, const void *searchobj)
{
	if (tree == NULL) {
		mge_errno = MGE_PARAM;
		return NULL;
	}
	return find_next_node(tree->root, searchobj, tree->comp);
}

/**
 * @cond INTERNAL
 * Find and return the next object.
 * Errors - mge_errno will be set as required.
 * @param currentnode - On invocation from user code this is the root node.
 * @param searchobj - The object to start from. It does not need to be a fully
 * populated object nor does the object need to exist. It only needs enough
 * information to support the comparison function. E.g. a key.
 * @param comp A pointer to the comparison function to be used.
 * @return Returns a pointer to the next object found in the tree, (i.e. a fully
 * populated object), or, NULL if not found or an error was encountered.
 */
static void *find_next_node(const struct bstreenode *currentnode,
			    const void *searchobj,
			    int (*comp)(const void *, const void *))
{
	void *nextobj = NULL;
	void *tmpobj = NULL;

	mge_errno = 0;

	if (searchobj == NULL || comp == NULL) {
		mge_errno = MGE_PARAM;
		return NULL;
	}

	if (currentnode == NULL)
		return NULL;

	if ((*comp)(searchobj, currentnode->object) < 0) {
		nextobj = currentnode->object;
		tmpobj = find_next_node(currentnode->childless, searchobj,
					comp);
		if (tmpobj != NULL)
			nextobj = tmpobj;
	} else if ((*comp)(searchobj, currentnode->object) >= 0) {
		tmpobj = find_next_node(currentnode->childgreater, searchobj,
					comp);
		if (tmpobj != NULL)
			nextobj = tmpobj;
	}
	return nextobj;
}
/* @endcond */

/**
 * Find the previous node.
 * Find and return the object attached to the previous node in the bst 'tree'.
 * On error mge_errno will be set.
 * @param tree The bst to search.
 * @param searchobj The object to find. It does not need to be a fully
 * populated object. It only needs enough information to support the comparison
 * function. E.g. a key.
 * @return A pointer to the preceding object in the tree, (i.e. a fully
 * populated object), or, NULL if not found or an error was encountered.
 */
void *find_prev_bst_node(const struct bstree *tree, const void *searchobj)
{
	if (tree == NULL) {
		mge_errno = MGE_PARAM;
		return NULL;
	}
	return find_prev_node(tree->root, searchobj, tree->comp);
}

/**
 * @cond INTERNAL
 * Find and return the previous object.
 * Errors - mge_errno will be set as required.
 * @param currentnode - On invocation from user code this is the root node.
 * @param searchobj - The object to start from. It does not need to be a fully
 * populated object nor does the object need to exist. It only needs enough
 * information to support the comparison function. E.g. a key.
 * @param comp A pointer to the comparison function to be used.
 * @return Returns a pointer to the preceding object in the tree, (i.e. a fully
 * populated object), or, NULL if not found or an error was encountered.
 */
static void *find_prev_node(const struct bstreenode *currentnode,
			    const void *searchobj,
			    int (*comp)(const void *, const void *))
{
	void *prevobj = NULL;
	void *tmpobj = NULL;

	mge_errno = 0;

	if (searchobj == NULL || comp == NULL) {
		mge_errno = MGE_PARAM;
		return NULL;
	}

	if (currentnode == NULL)
		return NULL;

	if ((*comp)(searchobj, currentnode->object) > 0) {
		prevobj = currentnode->object;
		tmpobj = find_prev_node(currentnode->childgreater, searchobj,
					comp);
		if (tmpobj != NULL)
			prevobj = tmpobj;
	} else if ((*comp)(searchobj, currentnode->object) <= 0) {
		tmpobj = find_prev_node(currentnode->childless, searchobj,
					comp);
		if (tmpobj != NULL)
			prevobj = tmpobj;
	}
	return prevobj;
}
/* @endcond */

/**
 * Update a node's object.
 * Update the object in a node in the bst 'tree'. (This only makes sense if the
 * object is carrying a payload.)
 * On error mge_errno will be set.
 * @param tree The bst to search.
 * @param updobj The object to update. The node is found and the existing
 * object is replaced with the new object.
 * @param objsize The size of the new object.
 * @return A pointer to the new object, or, NULL if not found or error.
 */
void *upd_bst_node(const struct bstree *tree, const void *updobj,
		   size_t objsize)
{
	if (tree == NULL) {
		mge_errno = MGE_PARAM;
		return NULL;
	}
	return upd_node(tree->root, updobj, objsize, tree->comp);
}

/**
 * @cond INTERNAL
 * Update the object. (This only makes sense if the object is carrying a
 * payload.)
 * Errors - mge_errno will be set as required.
 * @param currentnode - On invocation from user code this is the root node.
 * @param updobj - The object to update. The node is found and the existing
 * object is replaced with the new object.
 * @param objsize The size of the new object.
 * @param comp A pointer to the comparison function to be used.
 * @return Returns a pointer to the new object, or, NULL if not found or error.
 */
static void *upd_node(struct bstreenode *currentnode, const void *updobj,
		      size_t objsize, int (*comp)(const void *, const void *))
{
	void *newobj = NULL;

	if (updobj == NULL || !objsize || comp == NULL) {
		mge_errno = MGE_PARAM;
		return NULL;
	}

	if (currentnode == NULL)
		return NULL;

	mge_errno = MGE_NODE_NOT_FOUND;

	if ((*comp)(updobj, currentnode->object) == 0) {
		mge_errno = 0;
		free(currentnode->object);
		if ((currentnode->object = malloc(objsize)) != NULL) {
			newobj = memcpy(currentnode->object, updobj, objsize);
		} else {
			mge_errno = MGE_ERRNO;
			sav_errno = errno;
		}
	} else if ((*comp)(updobj, currentnode->object) < 0) {
		newobj = upd_node(currentnode->childless, updobj, objsize,
				  comp);
	} else if ((*comp)(updobj, currentnode->object) > 0) {
		newobj = upd_node(currentnode->childgreater, updobj, objsize,
				  comp);
	}
	return newobj;
}
/* @endcond */

/**
 * Delete a node.
 * Delete a node in the bst 'tree'. Re-links any children. If the node counter
 * is > 1 then duplicates are allowed and the counter is decremented instead of
 * deleting the node.
 * On error mge_errno will be set.
 * @param tree The bst to search.
 * @param searchobj The object to find. It does not need to be a fully
 * populated object. It only needs enough information to support the comparison
 * function. E.g. a key.
 * @return A pointer to the updated bst, or, NULL on error.
 */
struct bstree *del_bst_node(struct bstree *tree, const void *searchobj)
{
	struct bstreenode *delnode;

	if (tree == NULL) {
		mge_errno = MGE_PARAM;
		return NULL;
	}

	delnode = del_node(tree->root, searchobj, tree);
	if (mge_errno)
		return NULL;
	tree->root = delnode;
	return tree;
}

/**
 * @cond INTERNAL
 * Delete node. Re-links any children. If the node counter is > 1 then
 * duplicates are allowed and the counter is decremented instead of deleting the
 * node.
 * Errors - mge_errno will be 0 on sucess or set as required.
 * @param currentnode - On invocation from user code this is the root node.
 * @param searchobj - The object to find. It does not need to be a fully
 * populated object. It only needs enough information to support the comparison
 * function. E.g. a key.
 * @param tree The bst to search.
 * @return Returns to the calling function a pointer to the root node, or, NULL
 * if it was the last remaining node which was deleted. Also returns NULL on
 * some errors.
 */
static struct bstreenode *del_node(struct bstreenode *currentnode,
				   const void *searchobj, struct bstree *tree)
{
	struct bstreenode *p1, *p2;

	mge_errno = 0;

	if (currentnode == NULL) {
		mge_errno = MGE_NODE_NOT_FOUND;
		return NULL;
	}
	if (searchobj == NULL || tree->comp == NULL) {
		mge_errno = MGE_PARAM;
		return NULL;
	}

	/*
	 * This is the node to delete.
	 * The returned value will be attached to the parent node child less or
	 * greater depending on which branch we are descending.
	 */
	if ((*(tree->comp))(searchobj, currentnode->object) == 0) {
		mge_errno = 0; /* The node to delete exists */

		/*
		 * If the counter is > 1 then duplicates are allowed and all
		 * we need do is decrement the counter.
		 */
		if (currentnode->count > 1) {
			currentnode->count--;
			tree->count_total--;
			return currentnode;
		}

		/* A child-less node. */
		if (currentnode->childless == currentnode->childgreater) {
			free_bst_node(currentnode);
			tree->count_total--;
			tree->node_total--;
			return NULL;
		} else if (currentnode->childless == NULL) {
			/* Has only a greater child. */
			p1 = currentnode->childgreater;
			free_bst_node(currentnode);
			tree->count_total--;
			tree->node_total--;
			return p1;
		} else if (currentnode->childgreater == NULL) {
			/* Has only a lesser child. */
			p1 = currentnode->childless;
			free_bst_node(currentnode);
			tree->count_total--;
			tree->node_total--;
			return p1;
		} else {
			/* Has both children */
			p1 = currentnode->childless;
			p2 = currentnode->childless;
			/*
			 * From lesser child descend the greater branch until an
			 * empty child greater.
			 */
			while (p2->childgreater)
				p2 = p2->childgreater;
			/*
			 * Attach the orphan child greater into the empty slot.
			 */
			p2->childgreater = currentnode->childgreater;
			free_bst_node(currentnode);
			tree->count_total--;
			tree->node_total--;
			return p1;
		}
	}
	/* If not a match, descend the appropriate branch. */
	if ((*(tree->comp))(searchobj, currentnode->object) < 0)
		currentnode->childless
			= del_node(currentnode->childless, searchobj, tree);
	else
		currentnode->childgreater
			= del_node(currentnode->childgreater, searchobj, tree);

	return currentnode;
}
/* @endcond */

/**
 * Delete a bst.
 * Delete a binary search tree.
 * @param tree The bst to delete.
 * @return NULL
 */
struct bstree *del_bst(struct bstree *tree)
{
	free_bstree(tree->root);
	free(tree);
	return NULL;
}

/**
 * @cond INTERNAL
 * Free memory allocated to the bstree. Walks the tree deleting nodes.
 * @param currentnode The root node.
 * @return NULL
 */
static struct bstreenode *free_bstree(struct bstreenode *currentnode)
{
	mge_errno = 0;

	if (currentnode == NULL)
		return NULL;

	if (currentnode->childless != NULL)
		free_bstree(currentnode->childless);

	if (currentnode->childgreater != NULL)
		free_bstree(currentnode->childgreater);

	return free_bst_node(currentnode);
}
/* @endcond */

/**
 * @cond INTERNAL
 * Free memory allocated to the node. (Both node and object).
 * @param currentnode The node to free.
 * @return NULL
 */
static struct bstreenode *free_bst_node(struct bstreenode *currentnode)
{
	free(currentnode->object);
	free(currentnode);

	return NULL;
}
/* @endcond */

/**
 * Find and return the next object and it's coordinates in the bst 'tree'.
 * This is only really useful for testing purposes where this function can be
 * used to verify the tree coordinates of nodes.
 * On error mge_errno will be set.
 * @param tree The bst to search.
 * @param searchobj The object to find. It does not need to be a fully
 * populated object. It only needs enough information to support the comparison
 * function. E.g. a key.
 * @return A pointer to the next coordinate object found in the tree, (i.e. a
 * fully populated object), or, the actual node object will be NULL if not
 * found. Returns NULL on error.
 */
struct bstobjcoord *find_next_bst_node_trace(const struct bstree *tree,
					     struct bstobjcoord *searchobj)
{
	if (tree == NULL) {
		mge_errno = MGE_PARAM;
		return NULL;
	}
	return find_next_node_trace(tree->root, searchobj, tree->comp);
}

/**
 * @cond INTERNAL
 * Find and return the next object and it's coordinates.
 * This is only really useful for testing purposes where this function can be
 * used to verify the tree coordinates of nodes.
 * Errors - NULL will be returned and mge_errno will be set as required.
 * @param currentnode - On invocation from user code this is the root node.
 * @param searchobj - The trace object to start from. It does not need to be a
 * fully populated object nor does the object need to exist. It only needs
 * enough information to support the comparison function. E.g. a key.
 * @param comp A pointer to the comparison function to be used.
 * @return Returns a pointer to the next coordinate object found in the tree,
 * (i.e. a fully populated object), or, the actual node object will be NULL if
 * not found. Returns NULL on error.
 */
static struct bstobjcoord *
find_next_node_trace(const struct bstreenode *currentnode,
		     struct bstobjcoord *searchobj,
		     int (*comp)(const void *, const void *))
{
	static int x = 0, y = 0;
	struct bstobjcoord *nextcoord = searchobj;
	struct bstobjcoord tmpcoord = { NULL, 0, 0, 0 };

	mge_errno = 0;

	if (searchobj->object == NULL || comp == NULL) {
		mge_errno = MGE_PARAM;
		return NULL;
	}

	if (currentnode == NULL) {
		nextcoord->object = NULL;
		return nextcoord;
	}

	if ((*comp)(searchobj->object, currentnode->object) < 0) {
		tmpcoord.object = currentnode->object;
		tmpcoord.count = currentnode->count;
		tmpcoord.xdir = x--;
		tmpcoord.ydir = y++;
		nextcoord = find_next_node_trace(currentnode->childless,
						 searchobj, comp);

		if (nextcoord->object == NULL) {
			nextcoord->object = tmpcoord.object;
			nextcoord->count = tmpcoord.count;
			nextcoord->xdir = tmpcoord.xdir;
			nextcoord->ydir = tmpcoord.ydir;
		}
	} else if ((*comp)(searchobj->object, currentnode->object) >= 0) {
		tmpcoord.xdir = x++;
		tmpcoord.ydir = y++;
		nextcoord = find_next_node_trace(currentnode->childgreater,
						 searchobj, comp);
		if (nextcoord->object == NULL) {
			nextcoord->object = tmpcoord.object;
			nextcoord->count = tmpcoord.count;
			nextcoord->xdir = tmpcoord.xdir;
			nextcoord->ydir = tmpcoord.ydir;
		}
	}
	x = y = 0;
	return nextcoord;
}
/* @endcond */

