/**
 * @file src/prg/c/src/libmgec/listsandsorts/sllist.c
 *
 * Builds, traverses and releases a singly linked list.
 *
 * Build, manipulate and traverse functionality for singly linked lists.
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

#include <libmgec/mge-errno.h>
#include <libmgec/sllist.h>

static void free_sll_node(struct sllistnode *currentnode);

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
