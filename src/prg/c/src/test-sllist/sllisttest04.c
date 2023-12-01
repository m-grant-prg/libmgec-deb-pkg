/* **********************************************************************
 *									*
 * Author Copyright (C) 2019, 2021-2023  Mark Grant			*
 *									*
 * Purpose:								*
 *	SLL create and free test program using add_head.		*
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
#include <libmgec/libmgec.h>
#include <libmgec/mge-errno.h>
#include <libmgec/sllist.h>

int test04(void)
{
	const char *str[] = { "consistency", "is",   "all",  "i",   "ask",
			      "give",	     "us",   "this", "day", "our",
			      "daily",	     "mask", "\0" };
	int prog_error = 0;
	char result[500] = { '\0' };
	char *presult = result;
	FILE *fp;
	struct sllistnode *root = NULL;
	int i;

	if ((fp = fopen("./Test04Result.txt", "w")) == NULL) {
		printf("Cannot create result file.\n");
		printf("Test 04 failed.\n");
		return 1;
	}

	for (i = 0; *str[i] && !mge_errno; i++) {
		struct testnode test;
		strcpy(test.key, str[i]);
		test.payload = i;
		root = add_head_sll_node(root, &test, sizeof test);
		if (root == NULL)
			return 1;
		snprintf(presult, ARRAY_SIZE(result), "Add node - %s\n",
			 test.key);
		presult = emit_outputs(presult, fp);
	}

	snprintf(presult, ARRAY_SIZE(result),
		 "mge_errno after single linked list population:- %d\n",
		 mge_errno);
	presult = emit_outputs(presult, fp);

	if (mge_errno) {
		snprintf(presult, ARRAY_SIZE(result),
			 "Test 04 failed with error - %s\n",
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

	strcpy(presult, "Print list just before freeing list.\n");
	presult = emit_outputs(presult, fp);

	presult = printlist(root, presult);
	presult = emit_outputs(presult, fp);

	/* Test free_sllist */
	strcpy(presult, "Freeing tree.\n");
	presult = emit_outputs(presult, fp);

	root = free_sllist(root);
	presult = printlist(root, presult);
	presult = emit_outputs(presult, fp);

	snprintf(presult, ARRAY_SIZE(result),
		 "Root address after freeing is: %p\n", root);
	presult = emit_outputs(presult, fp);

	fclose(fp);

	prog_error = cmpresfile("./Test04Result.txt", "./Test04Answer.txt");

	if (!prog_error)
		printf("Test 04 passed.\n");
	else
		printf("Test 04 failed.\n");

	return prog_error;
}
