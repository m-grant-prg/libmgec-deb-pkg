/**
 * @file src/prg/c/src/libmgec/listsandsorts/sllist.c
 *
 * Builds, traverses and releases a singly linked list.
 *
 * Build, manipulate and traverse functionality for singly linked lists.
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
 * 05/07/2019	MG	1.0.9	clang-format coding style changes.	*
 *				Improve code legibility.		*
 *				Extract find_next_sll_node to header 	*
 *				file to make static inline.		*
 *				Improve parameter naming.		*
 *				%s/add_sll_node/add_tail_sll_node/g	*
 *				Add add_head_sll_node			*
 *				Add find_sll_node.			*
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

#include "sllist-internal.h"
#include <mge-errno.h>
#include <sllist.h>

/**
 * Add a node to the start of the singly linked list.
 * On error mge_errno will be set.
 * @param head A pointer to the current root node or NULL if the list is not yet
 * started.
 * @param object The object to attach to the node.
 * @param objsize The size of the attached object.
 * @return head, a pointer to the new root node or NULL on error
 */
struct sllistnode *add_head_sll_node(struct sllistnode *head,
				     const void *object, size_t objsize)
{
	struct sllistnode *newhead;

	if (object == NULL || !objsize) {
		mge_errno = MGE_PARAM;
		return NULL;
	}

	newhead = malloc(sizeof(struct sllistnode));
	if (newhead == NULL)
		goto node_fail;

	newhead->object = malloc(objsize);
	if (newhead->object == NULL)
		goto obj_fail;

	/* Copy object and initialise node. */
	newhead->object = memcpy(newhead->object, object, objsize);
	newhead->next = head;
	return newhead;

obj_fail:
	free(newhead);
node_fail:
	mge_errno = MGE_ERRNO;
	sav_errno = errno;
	return NULL;
}

/**
 * Add a node to the tail of the singly linked list.
 * On error mge_errno will be set.
 * @param head A pointer to the root node or NULL if the list is not yet
 * started.
 * @param object The object to attach to the node.
 * @param objsize The size of the attached object.
 * @return head, a pointer to the root node or NULL on error
 */
struct sllistnode *add_tail_sll_node(struct sllistnode *head,
				     const void *object, size_t objsize)
{
	if (object == NULL || !objsize) {
		mge_errno = MGE_PARAM;
		return NULL;
	}

	if (head == NULL) {
		/* At the tail, add the node */
		head = malloc(sizeof(struct sllistnode));
		if (head == NULL)
			goto node_fail;

		head->object = malloc(objsize);
		if (head->object == NULL)
			goto obj_fail;

		/* Copy object and initialise node. */
		head->object = memcpy(head->object, object, objsize);
		head->next = NULL;
	} else {
		/*
		 * Not yet at the tail, recurse onwards re-linking backwards on
		 * return
		 */
		head->next = add_tail_sll_node(head->next, object, objsize);
	}
	return head;

obj_fail:
	free(head);
node_fail:
	mge_errno = MGE_ERRNO;
	sav_errno = errno;
	return NULL;
}

/**
 * Find a node.
 * On error mge_errno will be set, otherwise it will be 0.
 * @param head A pointer to the current root node.
 * @param searchobj The object to find. It does not need to be a fully populated
 * object. It only needs enough inforamtion to support the comparison function,
 * eg a key.
 * @param comp A pointer to the comparison function to be used. This must have
 * the same shape as strcmp.
 * @return A pointer to the object found, (the fully populated object), or NULL
 * if not found or an error was encountered.
 */
void *find_sll_node(struct sllistnode *head, const void *searchobj,
		    int (*comp)(const void *, const void *))
{
	mge_errno = 0;

	if (searchobj == NULL || comp == NULL) {
		mge_errno = MGE_PARAM;
		return NULL;
	}

	if (head == NULL)
		return NULL;

	if ((*comp)(searchobj, head->object) == 0)
		return head->object;

	return find_sll_node(head->next, searchobj, comp);
}

/**
 * Free the entire list.
 * Walks the list deleting nodes.
 * @param head The root node.
 * @return NULL
 */
struct sllistnode *free_sllist(struct sllistnode *head)
{
	if (head == NULL)
		return NULL;

	/* Recurse to tail and delete backwards */
	if (head->next != NULL)
		free_sllist(head->next);

	free_sll_node(head);
	return NULL;
}

/**
 * @cond INTERNAL
 * Free memory allocated to the node. (Both node and object).
 * @param focus The node to free.
 */
static void free_sll_node(struct sllistnode *focus)
{
	free(focus->object);
	free(focus);
}
/* @endcond */

