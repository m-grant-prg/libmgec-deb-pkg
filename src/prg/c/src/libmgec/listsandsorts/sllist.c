/**
 * @file src/prg/c/src/libmgec/listsandsorts/sllist.c
 *
 * Builds, traverses and releases a singly linked list.
 *
 * Build, manipulate and traverse functionality for singly linked lists.
 *
 * @author Copyright (C) 2016-2019  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0
 *
 * @version _v1.0.9 ==== 09/06/2019_
 */

/* **********************************************************************
 *									*
 * Changelog								*
 *									*
 * Date		Author	Version	Description				*
 *									*
 * 05/05/2016	MG	1.0.1	First release.				*
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
 * 09/06/2019	MG	1.0.9	clang-format coding style changes.	*
 *									*
 ************************************************************************
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This must be included before internal.h */
#include <sllist.h>

#include "internal.h"
#include <mge-errno.h>

/**
 * Add a singly linked list node.
 * On error mge_errno will be set.
 * @param currentnode A pointer to the root node or NULL if the list is not yet
 * started.
 * @param object The object to attach to the node.
 * @param objsize The size of the attached object.
 * @return A pointer to the root node or NULL on error
 */
struct sllistnode *add_sll_node(struct sllistnode *currentnode,
				const void *object, size_t objsize)
{
	mge_errno = 0;

	if (object == NULL || !objsize) {
		mge_errno = MGE_PARAM;
		return NULL;
	}

	if (currentnode == NULL) {
		/* A new object */
		if ((currentnode = malloc(sizeof(struct sllistnode))) != NULL) {
			if ((currentnode->object = malloc(objsize)) != NULL) {
				/* Copy object and initialise node. */
				currentnode->object = memcpy(
					currentnode->object, object, objsize);
				currentnode->nextnode = NULL;
			} else {
				/* Cannot malloc object */
				mge_errno = MGE_ERRNO;
				sav_errno = errno;
				free(currentnode);
				currentnode = NULL;
			}
		} else {
			/* Cannot malloc node */
			mge_errno = MGE_ERRNO;
			sav_errno = errno;
		}
	} else
		currentnode->nextnode
			= add_sll_node(currentnode->nextnode, object, objsize);
	return currentnode;
}

/**
 * Find the next node in the list.
 * @param currentnode The current node.
 * @return A pointer to the next node found in the list, or NULL if no
 * subsequent node exists.
 */
struct sllistnode *find_next_sll_node(struct sllistnode *currentnode)
{
	mge_errno = 0;
	return currentnode->nextnode;
}

/**
 * Free the entire list.
 * Walks the list deleting nodes.
 * @param currentnode The root node.
 * @return NULL
 */
struct sllistnode *free_sllist(struct sllistnode *currentnode)
{
	mge_errno = 0;

	if (currentnode == NULL)
		return NULL;

	if (currentnode->nextnode != NULL)
		free_sllist(currentnode->nextnode);

	free_sll_node(currentnode);
	return NULL;
}

/*
 * Free memory allocated to the node. (Both node and object).
 */
static void free_sll_node(struct sllistnode *currentnode)
{
	free(currentnode->object);
	free(currentnode);
}

