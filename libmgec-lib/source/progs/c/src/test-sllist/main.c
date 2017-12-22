/* **********************************************************************
 *									*
 * Source: main.c							*
 * Author: Mark Grant							*
 *									*
 * Purpose:								*
 *	Test program for singly linked lists in libmgec shared library.	*
 * 									*
 * 									*
 * Released under the GPLv3 only.					*
 * SPDX-License-Identifier: GPL-3.0					*
 *									*
 ************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mge-errno.h>
#include <sllist.h>
#include <libmgec.h>

struct testnode {
	char key[20];
	int payload;
};

void printlist(struct sllistnode *root);
void testparamerr(struct sllistnode *root);

/*
 * sllist test program.
 */
int main(int argc, char** argv)
{
	int prog_error = 0;
	int i;

	struct testnode {
		char key[20];
		int payload;
	};

	struct sllistnode *root = NULL;

	printf("Words entered:-\t");
	char *str[] = {"give", "consistency", "is", "all", "i", "ask", "give",
			"us", "this", "day", "our", "daily", "mask", "\0"};
	for (i = 0; *str[i] && !mge_errno; i++) {
		printf("%s ", str[i]);
		struct testnode test;
		strcpy(test.key, str[i]);
		test.payload = i;
		root = add_sll_node(root, &test, sizeof test);
	}
	printf("\n");
	printf("mge_errno after single linked list population is %d\n",
		mge_errno);
	if (mge_errno)
		printf("%s\n", mge_strerror(mge_errno));
	printf("\n");

	printf("Print single linked list.\n");
	printlist(root);
	printf("\n");

	printf("Print 2nd time to ensure root node not corrupted.\n");
	printlist(root);
	printf("\n");

	/* Test param error. */
	testparamerr(root);
	printf("\n");

	printf("Print list just before freeing list.\n");
	printlist(root);

	/* Test free_sllist */
	printf("Freeing tree.\n");
	root = free_sllist(root);
	printlist(root);

	printf("Root address after freeing is: %p\n", root);
	printf("\n");

	libmgec_print_src_version();
	libmgec_print_pkg_version();

	exit(prog_error);
}

void printlist(struct sllistnode *root)
{
	struct testnode *pnode;
	struct sllistnode *currentnode;
	currentnode = root;

	printf("Linked List:-\t");

	while (currentnode != NULL) {
		pnode = currentnode->object;
		printf("%s ", pnode->key);
		currentnode = find_next_sll_node(currentnode);
	}
	printf("\n");
}

void testparamerr(struct sllistnode *root)
{
	struct testnode *node;
	node = NULL;
	printf("Adding object whose pointer value is  %p\n", node);
	root = add_sll_node(root, node, 10);
	printf("mge_errno value after add_sll_node is %d\n", mge_errno);
	if (mge_errno)
		printf("%s\n", mge_strerror(mge_errno));
	printf("Root is %p\n", root);
	printf("\n");
	struct testnode test;
	strcpy(test.key, "James");
	test.payload = 100;
	printf("Adding object whose size is  0\n");
	root = add_sll_node(root, &test, 0);
	printf("mge_errno value after add_sll_node is %d\n", mge_errno);
	if (mge_errno)
		printf("%s\n", mge_strerror(mge_errno));
	printf("Root is %p\n", root);

}
