/* **********************************************************************
 *									*
 * Source: sllisttest03.c						*
 * Author Copyright (C) 2019  Mark Grant				*
 *									*
 * Purpose:								*
 *	SLL test find next node.					*
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

int test03(void)
{
	int prog_error = 0;
	char result[500] = { '\0' };
	char *presult = result;
	FILE *fp;
	struct sllistnode *root = NULL;
	struct sllistnode *focus;
	struct testnode *pnode;

	if ((fp = fopen("./Test03Result.txt", "w")) == NULL) {
		printf("Cannot create result file.\n");
		printf("Test 03 failed.\n");
		return 1;
	}

	root = create_list(root);

	sprintf(presult, "mge_errno after single linked list population:- %d\n",
		mge_errno);
	presult = emit_outputs(presult, fp);

	if (mge_errno) {
		sprintf(presult, "Test 03 failed with error - %s\n",
			mge_strerror(mge_errno));
		printf("%s\n", presult);
		fputs(result, fp);
		fclose(fp);
		return mge_errno;
	}

	strcpy(presult, "Iterate through list using find next node.\n");
	presult = emit_outputs(presult, fp);

	focus = root;
	do {
		pnode = focus->object;
		sprintf(presult, "%s\n", pnode->key);
		presult = emit_outputs(presult, fp);
	} while ((focus = find_next_sll_node(focus)) != NULL);

	/* Test free_sllist */
	strcpy(presult, "Freeing tree.\n");
	presult = emit_outputs(presult, fp);

	root = free_sllist(root);
	presult = printlist(root, presult);
	presult = emit_outputs(presult, fp);

	sprintf(presult, "Root address after freeing is: %p\n", root);
	presult = emit_outputs(presult, fp);

	fclose(fp);

	prog_error = cmpresfile("./Test03Result.txt", "./Test03Answer.txt");

	if (!prog_error)
		printf("Test 03 passed.\n");
	else
		printf("Test 03 failed.\n");

	return prog_error;
}

