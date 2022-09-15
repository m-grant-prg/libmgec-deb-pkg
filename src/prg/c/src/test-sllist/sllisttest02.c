/* **********************************************************************
 *									*
 * Source: sllisttest02.c						*
 * Author Copyright (C) 2019, 2021, 2022  Mark Grant			*
 *									*
 * Purpose:								*
 *	SLL parameter errors test program.				*
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

#include "sllisttest.h"
#include <libmgec.h>
#include <mge-errno.h>
#include <sllist.h>

int test02(void)
{
	int prog_error = 0;
	char result[500] = { '\0' };
	char *presult = result;
	FILE *fp;
	struct sllistnode *root = NULL;
	struct testnode *node;
	struct testnode test;

	if ((fp = fopen("./Test02Result.txt", "w")) == NULL) {
		printf("Cannot create result file.\n");
		printf("Test 02 failed.\n");
		return 1;
	}

	root = create_list(root);

	snprintf(presult, ARRAY_SIZE(result),
		 "mge_errno after single linked list population:- %d\n",
		 mge_errno);
	presult = emit_outputs(presult, fp);

	if (mge_errno) {
		snprintf(presult, ARRAY_SIZE(result),
			 "Test 02 failed with error - %s\n",
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

	/* Try adding a NULL node */
	node = NULL;
	snprintf(presult, ARRAY_SIZE(result),
		 "Adding object whose pointer value is  %p\n", node);
	presult = emit_outputs(presult, fp);
	add_tail_sll_node(root, node, 10);
	snprintf(presult, ARRAY_SIZE(result),
		 "mge_errno after add_tail_sll_node is %d\n", mge_errno);
	presult = emit_outputs(presult, fp);
	if (mge_errno) {
		snprintf(presult, ARRAY_SIZE(result), "%s\n",
			 mge_strerror(mge_errno));
		presult = emit_outputs(presult, fp);
	}

	/* Try adding node with object size 0 */
	strcpy(test.key, "James");
	test.payload = 100;
	snprintf(presult, ARRAY_SIZE(result),
		 "Adding object whose size is  0\n");
	presult = emit_outputs(presult, fp);
	add_tail_sll_node(root, &test, 0);
	snprintf(presult, ARRAY_SIZE(result),
		 "mge_errno after add_tail_sll_node is %d\n", mge_errno);
	presult = emit_outputs(presult, fp);
	if (mge_errno) {
		snprintf(presult, ARRAY_SIZE(result), "%s\n",
			 mge_strerror(mge_errno));
		presult = emit_outputs(presult, fp);
	}

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

	snprintf(presult, ARRAY_SIZE(result),
		 "Root address after freeing is: %p\n", root);
	presult = emit_outputs(presult, fp);

	fclose(fp);

	prog_error = cmpresfile("./Test02Result.txt", "./Test02Answer.txt");

	if (!prog_error)
		printf("Test 02 passed.\n");
	else
		printf("Test 02 failed.\n");

	return prog_error;
}
