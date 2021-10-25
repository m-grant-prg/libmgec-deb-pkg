/* **********************************************************************
 *									*
 * Source: sllisttest05.c						*
 * Author Copyright (C) 2019  Mark Grant				*
 *									*
 * Purpose:								*
 *	Test find_sll_node.						*
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

#include "sllisttest.h"
#include <mge-errno.h>
#include <sllist.h>

int test05(void)
{
	int prog_error = 0;
	char result[500] = { '\0' };
	char *presult = result;
	FILE *fp;
	struct sllistnode *root = NULL;
	struct testnode name = { "Jim", 0 };
	struct testnode *node;
	struct testnode test;
	struct testnode test1;

	if ((fp = fopen("./Test05Result.txt", "w")) == NULL) {
		printf("Cannot create result file.\n");
		printf("Test 05 failed.\n");
		return 1;
	}

	root = create_list(root);

	sprintf(presult, "mge_errno after single linked list population:- %d\n",
		mge_errno);
	presult = emit_outputs(presult, fp);

	if (mge_errno) {
		sprintf(presult, "Test 05 failed with error - %s\n",
			mge_strerror(mge_errno));
		printf("%s\n", presult);
		fputs(result, fp);
		fclose(fp);
		return mge_errno;
	}

	strcpy(presult, "Print single linked list.\n");
	presult = emit_outputs(presult, fp);

	presult = printlist(root, presult);
	presult = emit_outputs(presult, fp);

	/* Try finding non-existent object */

	sprintf(presult, "Trying to find node with key %s\n", name.key);
	presult = emit_outputs(presult, fp);
	node = find_sll_node(root, &name, nodecmp);
	sprintf(presult, "mge_errno after find_sll_node is %d\n", mge_errno);
	presult = emit_outputs(presult, fp);

	sprintf(presult, "Node address returned is: %p\n", node);
	presult = emit_outputs(presult, fp);

	/* Try finding root node */
	strcpy(test.key, "give");
	test.payload = 0;
	sprintf(presult, "Looking for root node\n");
	presult = emit_outputs(presult, fp);
	node = find_sll_node(root, &test, nodecmp);
	sprintf(presult, "mge_errno after find_sll_node is %d\n", mge_errno);
	presult = emit_outputs(presult, fp);
	if (mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		presult = emit_outputs(presult, fp);
	}
	sprintf(presult, "Node found with key %s\n", node->key);
	presult = emit_outputs(presult, fp);

	/* Try finding non-root node */
	strcpy(test1.key, "this");
	test1.payload = 0;
	sprintf(presult, "Looking for non-root node\n");
	presult = emit_outputs(presult, fp);
	node = find_sll_node(root, &test1, nodecmp);
	sprintf(presult, "mge_errno after find_sll_node is %d\n", mge_errno);
	presult = emit_outputs(presult, fp);
	if (mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		presult = emit_outputs(presult, fp);
	}
	sprintf(presult, "Node found with key %s\n", node->key);
	presult = emit_outputs(presult, fp);

	/* Tidy up and go */
	strcpy(presult, "Print list just before freeing list.\n");
	presult = emit_outputs(presult, fp);
	presult = printlist(root, presult);
	presult = emit_outputs(presult, fp);

	/* Free_sllist */
	strcpy(presult, "Freeing tree.\n");
	presult = emit_outputs(presult, fp);
	root = free_sllist(root);
	presult = printlist(root, presult);
	presult = emit_outputs(presult, fp);

	sprintf(presult, "Root address after freeing is: %p\n", root);
	presult = emit_outputs(presult, fp);

	fclose(fp);

	prog_error = cmpresfile("./Test05Result.txt", "./Test05Answer.txt");

	if (!prog_error)
		printf("Test 05 passed.\n");
	else
		printf("Test 05 failed.\n");

	return prog_error;
}

