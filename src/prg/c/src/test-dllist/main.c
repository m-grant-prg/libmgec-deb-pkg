/* **********************************************************************
 *									*
 * Author Copyright (C) 2017-2019, 2021, 2023  Mark Grant		*
 *									*
 * Purpose:								*
 *	Test program for doubly linked lists in libmgec shared library.	*
 * 									*
 * 									*
 * Released under the GPLv3 only.					*
 * SPDX-License-Identifier: GPL-3.0-only				*
 *									*
 ************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libmgec/dllist.h>
#include <libmgec/libmgec.h>
#include <libmgec/mge-errno.h>

struct testnode {
	char key[20];
	int payload;
};

void printlist(struct dllistnode *root);
void printrevlist(struct dllistnode *root);
void testparamerr(struct dllistnode *root);

/*
 * dllist test program.
 */
int main(void)
{
	const char *str[] = { "give", "consistency", "is",   "all",  "i",
			      "ask",  "give",	     "us",   "this", "day",
			      "our",  "daily",	     "mask", "\0" };
	int prog_error = 0;
	int i;

	struct testnode {
		char key[20];
		int payload;
	};
	struct testnode test;

	struct dllistnode *root = NULL;

	printf("Words entered:-\t");
	for (i = 0; *str[i] && !mge_errno; i++) {
		printf("%s ", str[i]);
		strcpy(test.key, str[i]);
		test.payload = i;
		root = add_dll_node(root, &test, sizeof test);
	}
	printf("\n");
	printf("mge_errno after double linked list population is %d\n",
	       mge_errno);
	if (mge_errno)
		printf("%s\n", mge_strerror(mge_errno));
	printf("\n");

	printf("Print double linked list.\n");
	printlist(root);
	printf("\n");

	printf("Print 2nd time to ensure root node not corrupted.\n");
	printlist(root);
	printf("\n");

	printrevlist(root);
	printf("\n");

	/* Test param error. */
	testparamerr(root);
	printf("\n");

	printf("Print list just before freeing list.\n");
	printlist(root);

	/* Test free_dllist */
	printf("Freeing tree.\n");
	root = free_dllist(root);
	printlist(root);

	printf("Root address after freeing is: %p\n", root);
	printf("\n");

	libmgec_print_src_version();
	libmgec_print_pkg_version();

	exit(prog_error);
}

void printlist(struct dllistnode *root)
{
	struct testnode *pnode;
	struct dllistnode *currentnode;
	currentnode = root;

	printf("Linked List:-\t");

	while (currentnode != NULL) {
		pnode = currentnode->object;
		printf("%s ", pnode->key);
		currentnode = find_next_dll_node(currentnode);
	}
	printf("\n");
}

void printrevlist(struct dllistnode *root)
{
	struct testnode *pnode;
	struct dllistnode *currentnode;
	struct dllistnode *beforenode = NULL;
	currentnode = root;

	printf("Linked List in reverse:-\t");

	while (currentnode != NULL) {
		beforenode = currentnode;
		currentnode = find_next_dll_node(currentnode);
	}
	currentnode = beforenode;

	while (currentnode != NULL) {
		pnode = currentnode->object;
		printf("%s ", pnode->key);
		currentnode = find_prev_dll_node(currentnode);
	}
	printf("\n");
}

void testparamerr(struct dllistnode *root)
{
	struct testnode *node;
	struct testnode test;

	node = NULL;
	printf("Adding object whose pointer value is  %p\n", node);
	root = add_dll_node(root, node, 10);
	printf("mge_errno value after add_dll_node is %d\n", mge_errno);
	if (mge_errno)
		printf("%s\n", mge_strerror(mge_errno));
	printf("Root is %p\n", root);
	printf("\n");
	strcpy(test.key, "James");
	test.payload = 100;
	printf("Adding object whose size is  0\n");
	root = add_dll_node(root, &test, 0);
	printf("mge_errno value after add_dll_node is %d\n", mge_errno);
	if (mge_errno)
		printf("%s\n", mge_strerror(mge_errno));
	printf("Root is %p\n", root);
}
