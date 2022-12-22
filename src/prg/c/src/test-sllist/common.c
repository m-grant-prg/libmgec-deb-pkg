/* **********************************************************************
 *									*
 * Source: common.c							*
 * Author Copyright (C) 2019, 2021, 2022  Mark Grant			*
 *									*
 * Purpose:								*
 *	Common test functions for use in tests on singly linked lists	*
 *	in libmgec shared library.					*
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

/*
 * Create test list
 */
struct sllistnode *create_list(struct sllistnode *root)
{
	int i;

	char *str[] = { "give", "consistency", "is",   "all",  "i",
			"ask",	"give",	       "us",   "this", "day",
			"our",	"daily",       "mask", "\0" };
	for (i = 0; *str[i] && !mge_errno; i++) {
		struct testnode test;
		strcpy(test.key, str[i]);
		test.payload = i;
		root = add_tail_sll_node(root, &test, sizeof test);
		if (root == NULL)
			return NULL;
	}
	return root;
}

/*
 * Print the list to an output char buffer.
 */
char *printlist(struct sllistnode *root, char *output)
{
	struct testnode *pnode;
	struct sllistnode *currentnode;
	char tmpoutput[100];

	currentnode = root;

	strcat(output, "Linked List:-\t");

	for_each_sll_node (currentnode, root) {
		pnode = currentnode->object;
		snprintf(tmpoutput, ARRAY_SIZE(tmpoutput), "%s ", pnode->key);
		strcat(output, tmpoutput);
	}
	strcat(output, "\n");
	return output;
}

/*
 * Compare the test result file to the pre-determined test answer file.
 */
int cmpresfile(char *result, char *answer)
{
	FILE *fp, *fp1;
	int status = 0;
	char ans[500] = { '\0' };
	char res[500] = { '\0' };
	char *pans = ans;
	char *pres = res;

	if ((fp = fopen(result, "r")) == NULL) {
		printf("Cannot open result file.\n");
		return 1;
	}
	if ((fp1 = fopen(answer, "r")) == NULL) {
		printf("Cannot open answer file.\n");
		fclose(fp);
		return 1;
	}

	while (!feof(fp) && !feof(fp1)) {
		pres = fgets(pres, 498, fp);
		if (ferror(fp)) {
			printf("Cannot read result file.\n");
			return 1;
		}
		pans = fgets(pans, 498, fp1);
		if (ferror(fp1)) {
			printf("Cannot read answer file.\n");
			return 1;
		}
		if ((pres == NULL) && (pans == NULL)) {
			break;
		} else if ((pres == NULL) || (pans == NULL)) {
			status = 1;
			break;
		}
		if (strcmp(pres, pans)) {
			status = 1;
			break;
		}
	}

	fclose(fp);
	fclose(fp1);

	return status;
}

/*
 * Write buffer to file, and if verbose, write to stdout.
 */
char *emit_outputs(char *pr, FILE *fp)
{
	if (verbose)
		printf("%s\n", pr);
	fputs(pr, fp);
	*pr = '\0';
	return pr;
}

/*
 * node comparison function.
 */
int nodecmp(const void *node1, const void *node2)
{
	return (strcmp(((struct testnode *)node1)->key,
		       ((struct testnode *)node2)->key));
}
