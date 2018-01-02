/**
 * @file lib/source/progs/c/src/libmgec/listsandsorts/dllist.c
 *
 * Builds, traverses and releases a doubly linked list.
 *
 * Build, manipulate and bi-directional traverse functionality for doubly
 * linked lists.
 *
 * @author Copyright (C) 2016-2018  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0
 *
 * @version _v1.0.7 ==== 02/01/2018_
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
 *									*
 ************************************************************************
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <mge-errno.h>
#include <dllist.h>

/* Free memory allocated to the node. */
static void free_dll_node(struct dllistnode *currentnode);

/* Holds the address of the preceding node when adding nodes. */
static struct dllistnode *priornode = NULL;


/**
 * Add a doubly linked list node.
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
	mge_errno = 0;

	if (object == NULL || !objsize) {
		mge_errno = MGE_PARAM;
		return NULL;
	}

	if (currentnode == NULL) { // A new object.
		if ((currentnode =
			(struct dllistnode *) malloc(sizeof(struct dllistnode)))
			!= NULL) {
			if ((currentnode->object = malloc(objsize)) != NULL) {
				/* Copy object and initialise node. */
				currentnode->object =
					memcpy(currentnode->object, object,
						objsize);
				currentnode->prevnode = priornode;
				currentnode->nextnode = NULL;
			}
			else { // Cannot malloc object.
				mge_errno = MGE_ERRNO;
				sav_errno = errno;
				free(currentnode);
				currentnode = NULL;
			}
		}
		else { // Cannot malloc node.
			mge_errno = MGE_ERRNO;
			sav_errno = errno;
		}
	}
	else {
		priornode = currentnode;
		/* Move along list. */
		currentnode->nextnode = add_dll_node(currentnode->nextnode,
							object, objsize);
	}
	return currentnode;
}

/**
 * Find and return the previous node.
 * @param currentnode The current node.
 * @return A pointer to the previous node in the list or NULL if no previous
 * node exists.
 */
struct dllistnode *find_prev_dll_node(struct dllistnode *currentnode)
{
	mge_errno = 0;
	return currentnode->prevnode;
}

/**
 * Find and return the next node.
 * @param currentnode The current node.
 * @return A pointer to the next node in the list or NULL if no subsequent
 * node exists.
 */
struct dllistnode *find_next_dll_node(struct dllistnode *currentnode)
{
	mge_errno = 0;
	return currentnode->nextnode;
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
	mge_errno = 0;

	if (currentnode == NULL)
		return NULL;

	if (currentnode->nextnode != NULL)
		free_dllist(currentnode->nextnode);

	free_dll_node(currentnode);
	return NULL;
}

/*
 * Free memory allocated to the node. (Both node and object).
 */
static void free_dll_node(struct dllistnode *currentnode)
{
	free(currentnode->object);
	free(currentnode);
}
