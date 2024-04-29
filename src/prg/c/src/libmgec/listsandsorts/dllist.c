/**
 * @file src/prg/c/src/libmgec/listsandsorts/dllist.c
 *
 * Builds, traverses and releases a doubly linked list.
 *
 * Build, manipulate and bi-directional traverse functionality for doubly
 * linked lists.
 *
 * @author Copyright (C) 2016-2023  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.1.0 ==== 02/11/2023_
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libmgec/dllist.h>
#include <libmgec/mge-errno.h>

static void free_dll_node(struct dllistnode *currentnode);

/**
 * @cond INTERNAL
 * Holds the address of the preceding node when adding nodes.
 */
static struct dllistnode *priornode = NULL;
/* @endcond */

/**
 * Add a node to the tail of the doubly linked list.
 * On error mge_errno will be set.
 * @param currentnode A pointer to the first node or NULL if list not yet
 * started.
 * @param object Object to be attached to the node.
 * @param objsize Size of object.
 * @return A pointer to the first node. Returns NULL on error.
 */
struct dllistnode *add_dll_node(struct dllistnode *currentnode,
				const void *object, size_t objsize)
{
	if (object == NULL || !objsize) {
		mge_errno = MGE_PARAM;
		return NULL;
	}

	if (currentnode == NULL) {
		/* At the tail, add the node */
		currentnode = malloc(sizeof(struct dllistnode));
		if (currentnode == NULL)
			goto node_fail;

		currentnode->object = malloc(objsize);
		if (currentnode->object == NULL)
			goto obj_fail;

		/* Copy object and initialise node. */
		currentnode->object
			= memcpy(currentnode->object, object, objsize);
		currentnode->prevnode = priornode;
		currentnode->nextnode = NULL;
	} else {
		/*
		 * Not yet at the tail, recurse onwards re-linking backwards on
		 * return.
		 */
		priornode = currentnode;
		currentnode->nextnode
			= add_dll_node(currentnode->nextnode, object, objsize);
	}
	return currentnode;

obj_fail:
	free(currentnode);
node_fail:
	mge_errno = MGE_ERRNO;
	sav_errno = errno;
	return NULL;
}

/**
 * Free the entire list.
 * Remove all nodes and free memory allocated to the dllist. Walks the list
 * deleting nodes.
 * @param currentnode The root node.
 * @return NULL
 */
struct dllistnode *free_dllist(struct dllistnode *currentnode)
{
	if (currentnode == NULL)
		return NULL;

	if (currentnode->nextnode != NULL)
		free_dllist(currentnode->nextnode);

	free_dll_node(currentnode);
	return NULL;
}

/**
 * @cond INTERNAL
 * Free memory allocated to the node. (Both node and object).
 * @param currentnode The node to free.
 */
static void free_dll_node(struct dllistnode *currentnode)
{
	free(currentnode->object);
	free(currentnode);
}
/* @endcond */
