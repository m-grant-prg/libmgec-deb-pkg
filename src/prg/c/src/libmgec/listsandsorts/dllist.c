/**
 * @file src/prg/c/src/libmgec/listsandsorts/dllist.c
 *
 * Builds, traverses and releases a doubly linked list.
 *
 * Build, manipulate and bi-directional traverse functionality for doubly
 * linked lists.
 *
 * @author Copyright (C) 2016-2021  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.0.12 ==== 03/12/2021_
 */

/* **********************************************************************
 *									*
 * Changelog								*
 *									*
 * Date		Author	Version	Description				*
 *									*
 * 06/05/2016	MG	1.0.1	First release.				*
 * 16/07/2016	MG	1.0.2	Move towards kernel coding style.	*
 * 17/07/2016	MG	1.0.3	Further coding style change.		*
 * 03/05/2017	MG	1.0.4	Return NULL pointer, -1 or error number	*
 *				when possible on error.			*
 *				Apply coding standards from template	*
 *				atclstv v1.0.0				*
 *				Introduce library-wide mge_errno	*
 *				variable and error handling.		*
 * 05/11/2017	MG	1.0.5	Add Doxygen comments.			*
 * 09/11/2017	MG	1.0.6	Add SPDX license tag.			*
 * 02/01/2018	MG	1.0.7	Move to new source directory structure.	*
 * 19/05/2018	MG	1.0.8	Extract prototypes to internal.h	*
 * 11/06/2019	MG	1.0.9	clang-format coding style changes.	*
 *				Improve code legibility.		*
 *				Extract find_prev and find_next to the	*
 *				header file and make inline.		*
 * 12/07/2019	MG	1.0.10	Change to specific internal header file.*
 * 29/06/2020	MG	1.0.11	Add internal-only documentation of	*
 *				static (non-API) function.		*
 * 03/12/2021	MG	1.0.12	Tighten SPDX tag.			*
 *									*
 ************************************************************************
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dllist-internal.h"
#include <dllist.h>
#include <mge-errno.h>

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

