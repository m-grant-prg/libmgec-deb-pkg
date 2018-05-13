/* **********************************************************************
 *									*
 * Source: main.c							*
 * Author: Mark Grant							*
 *									*
 * Purpose:								*
 *	Test program for binary search trees in libmgec shared library.	*
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

#include <bstree.h>
#include <mge-errno.h>
#include <libmgec.h>

struct testnode {
	char key[20];
	int payload;
};

static int verbose;


int nodecmp(const struct testnode *node1, const struct testnode *node2);
struct bstree *pop_tree(struct bstree *tree, int duplicates);
char *printtree(struct bstree *root, char *output);
int cmpresfile(char *result, char *answer);
int test_tree_pop(void);
int testfind_bst_node(void);
int testget_counter_bst_node(void);
int testfind_next_bst_node(void);
int testfind_prev_bst_node(void);
int testupd_bst_node(void);
int testdel_bst_node(void);
int testdelonlynode(void);
int testdeldupnode(void);
int testaddduptounique(void);


/*
 * bstree test program.
 */
int main(int argc, char** argv)
{
	int i;
	int status = 0, status1 = 0;
	char choice[10] = { '\0' };
	char *pchoice = choice;

	struct testnode {
		char key[20];
		int payload;
	};


	printf("Choose one of :-\n");
	printf("a) Test  1 - Load bstree and report.\n");
	printf("b) Test  1 - Load bstree and report - verbose.\n");
	printf("c) Test  2 - Find bst node.\n");
	printf("d) Test  2 - Find bst node - verbose.\n");
	printf("e) Test  3 - Get counter.\n");
	printf("f) Test  3 - Get counter - verbose.\n");
	printf("g) Test  4 - Find next node.\n");
	printf("h) Test  4 - Find next node - verbose.\n");
	printf("i) Test  5 - Find previous node.\n");
	printf("j) Test  5 - Find previous node - verbose.\n");
	printf("k) Test  6 - Update node.\n");
	printf("l) Test  6 - Update node - verbose.\n");
	printf("m) Test  7 - Delete node.\n");
	printf("n) Test  7 - Delete node - verbose.\n");
	printf("o) Test  8 - Delete only node.\n");
	printf("p) Test  8 - Delete only node - verbose.\n");
	printf("q) Test  9 - Delete duplicate node.\n");
	printf("r) Test  9 - Delete duplicate node - verbose.\n");
	printf("s) Test 10 - Attempt add duplicate node to unique tree.\n");
	printf("t) Test 10 - Attempt add duplicate node to unique tree - "
		"verbose.\n");
	printf("u) Run all Tests.\n");
	printf("v) Run all Tests - verbose.\n");
	printf("\n[Choice]: ");

	i = scanf("%1s", choice);

	if (i != 1) {
		printf("Input error.");
		exit(1);
	}

	switch (*pchoice) {
	case 'a':
		verbose = 0;
		status = test_tree_pop();
		break;
	case 'b':
		verbose = 1;
		status = test_tree_pop();
		break;
	case 'c':
		verbose = 0;
		status = testfind_bst_node();
		break;
	case 'd':
		verbose = 1;
		status = testfind_bst_node();
		break;
	case 'e':
		verbose = 0;
		status = testget_counter_bst_node();
		break;
	case'f':
		verbose = 1;
		status = testget_counter_bst_node();
		break;
	case 'g':
		verbose = 0;
		status = testfind_next_bst_node();
		break;
	case 'h':
		verbose = 1;
		status = testfind_next_bst_node();
		break;
	case 'i':
		verbose = 0;
		status = testfind_prev_bst_node();
		break;
	case 'j':
		verbose = 1;
		status = testfind_prev_bst_node();
		break;
	case 'k':
		verbose = 0;
		status = testupd_bst_node();
		break;
	case 'l':
		verbose = 1;
		status = testupd_bst_node();
		break;
	case 'm':
		verbose = 0;
		status = testdel_bst_node();
		break;
	case 'n':
		verbose = 1;
		status = testdel_bst_node();
		break;
	case 'o':
		verbose = 0;
		status = testdelonlynode();
		break;
	case 'p':
		verbose = 1;
		status = testdelonlynode();
		break;
	case 'q':
		verbose = 0;
		status = testdeldupnode();
		break;
	case 'r':
		verbose = 1;
		status = testdeldupnode();
		break;
	case 's':
		verbose = 0;
		status = testaddduptounique();
		break;
	case 't':
		verbose = 1;
		status = testaddduptounique();
		break;
	case 'u':
		verbose = 0;
		status1 = test_tree_pop();
		if (status1)
			status = 1;
		status1 = testfind_bst_node();
		if (status1)
			status = 1;
		status1 = testget_counter_bst_node();
		if (status1)
			status = 1;
		status1 = testfind_next_bst_node();
		if (status1)
			status = 1;
		status1 = testfind_prev_bst_node();
		if (status1)
			status = 1;
		status1 = testupd_bst_node();
		if (status1)
			status = 1;
		status1 = testdel_bst_node();
		if (status1)
			status = 1;
		status1 = testdelonlynode();
		if (status1)
			status = 1;
		status1 = testdeldupnode();
		if (status1)
			status = 1;
		status1 = testaddduptounique();
		if (status1)
			status = 1;
		break;
	case 'v':
		verbose = 1;
		status1 = test_tree_pop();
		if (status1)
			status = 1;
		status1 = testfind_bst_node();
		if (status1)
			status = 1;
		status1 = testget_counter_bst_node();
		if (status1)
			status = 1;
		status1 = testfind_next_bst_node();
		if (status1)
			status = 1;
		status1 = testfind_prev_bst_node();
		if (status1)
			status = 1;
		status1 = testupd_bst_node();
		if (status1)
			status = 1;
		status1 = testdel_bst_node();
		if (status1)
			status = 1;
		status1 = testdelonlynode();
		if (status1)
			status = 1;
		status1 = testdeldupnode();
		if (status1)
			status = 1;
		status1 = testaddduptounique();
		if (status1)
			status = 1;
		break;
	default:
		printf("Invalid selection.\n");
		break;
	}


	libmgec_print_src_version();
	libmgec_print_pkg_version();

	exit(status);
}

/*
 *bst node comparison function.
 */
int nodecmp(const struct testnode *node1, const struct testnode *node2)
{
	return (strcmp(node1->key, node2->key));
}

/*
 * Popluate a standard testing btree.
 */
struct bstree *pop_tree(struct bstree *tree, int duplicates)
{

	struct bstree *res;
	int i;

	res = cre_bst(duplicates, (int (*)(const void *, const void *))nodecmp);
	if (res == NULL) {
		if (verbose)
			printf("%s\n", mge_strerror(mge_errno));
		del_bst(tree);
		return NULL;
	}
	tree = res;

	if (verbose)
		printf("Words entered:-\t");
	char *str[] = {"consistency", "is", "all", "i", "ask", "give",
			"us", "this", "day", "our", "daily", "mask", "\0"};
	for (i = 0; *str[i] && !mge_errno; i++) {
		if (verbose)
			printf("%s ", str[i]);
		struct testnode test;
		strcpy(test.key, str[i]);
		test.payload = i;
		res = add_bst_node(tree, &test, sizeof test);
		if (res == NULL) {
			if (verbose)
				printf("%s\n", mge_strerror(mge_errno));
			del_bst(tree);
			return NULL;
		}
		tree = res;
	}
	if (verbose)
		printf("\n");

	return tree;
}

/*
 * Print the bst.
 */
char *printtree(struct bstree *tree, char *output)
{
	struct testnode *pnode;
	struct testnode node;
	struct bstobjcoord objcoord;
	struct bstobjcoord *pobjcoord, *tmppobjcoord;
	char tmpoutput[100];

	strcpy(node.key, "");
	objcoord.object = &node;
	objcoord.xdir = objcoord.ydir = 0;
	pobjcoord = &objcoord;

	tmppobjcoord = find_next_bst_node_trace(tree, pobjcoord);
	if (tmppobjcoord != NULL)
		pobjcoord = tmppobjcoord;

	while (pobjcoord->object != NULL) {
		pnode = objcoord.object;
		sprintf(tmpoutput, "(%i, %i)%s[%i]\t", objcoord.xdir,
			objcoord.ydir, pnode->key, objcoord.count);
		strcat(output, tmpoutput);
		pobjcoord = find_next_bst_node_trace(tree, pobjcoord);
	}

	if (verbose)
		printf("Ordered:-\t%s\n", output);
	return output;
}

/*
 * Compare the test result file to the pre-determined test answer file.
 */
int cmpresfile(char *result, char *answer)
{
	FILE *fp, *fp1;
	int status = 0;
	char ans[500] = {'\0' };
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
 * Test 1.
 * Test the population of the bst.
 */
int test_tree_pop(void)
{

	char result[500] = { '\0' };
	char *presult = result;
	int status;
	struct bstree *tree = NULL;
	FILE *fp;

	tree = pop_tree(tree, BST_NODES_DUPLICATES);
	if (tree == NULL) {
		if (verbose)
			printf("Populate binary search tree failed.\n");
		return 1;
	}

	if ((fp = fopen("./Test01Result.txt", "w")) == NULL) {
		printf("Cannot create result file.\n");
		return 1;
	}
	presult = printtree(tree, presult);
	fputs(result, fp);
	fclose(fp);

	status = cmpresfile("./Test01Result.txt", "./Test01Answer.txt");

	tree = del_bst(tree);

	if (!status)
		printf("Test 1 passed.\n");
	else
		printf("Test 1 failed.\n");

	return status;
}

/*
 * Test 2.
 * Test the find node function.
 */
int testfind_bst_node(void)
{
	char result[500] = { '\0' };
	char *presult = result;
	struct bstree *tree = NULL;
	struct testnode *pnode;
	struct testnode node2;
	int status = 0;
	FILE *fp;

	tree = pop_tree(tree, BST_NODES_UNIQUE);
	if (tree == NULL) {
		if (verbose)
			printf("Populate binary search tree failed.\n");
		return 1;
	}

	if ((fp = fopen("./Test02Result.txt", "w")) == NULL) {
		printf("Cannot create result file.\n");
		return 1;
	}


	strcpy(node2.key, "aaa");
	pnode = find_bst_node(tree, &node2);
	if (pnode)
		sprintf(presult, "Find %s found %s payload %d with mge_errno "
			"%d\n", node2.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Find %s found %s with mge_errno %d\n",
			node2.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	struct testnode node3;
	strcpy(node3.key, "all");
	pnode = find_bst_node(tree, &node3);
	if (pnode)
		sprintf(presult, "Find %s found %s payload %d with mge_errno "
			"%d\n", node3.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Find %s found %s with mge_errno %d\n",
			node3.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	struct testnode node4;
	strcpy(node4.key, "ask");
	pnode = find_bst_node(tree, &node4);
	if (pnode)
		sprintf(presult, "Find %s found %s payload %d with mge_errno "
			"%d\n", node4.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Find %s found %s with mge_errno %d\n",
			node4.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	struct testnode node5;
	strcpy(node5.key, "this");
	pnode = find_bst_node(tree, &node5);
	if (pnode)
		sprintf(presult, "Find %s found %s payload %d with mge_errno "
			"%d\n", node5.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Find %s found %s with mge_errno %d\n",
			node5.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	struct testnode node6;
	strcpy(node6.key, "thiss");
	pnode = find_bst_node(tree, &node6);
	if (pnode)
		sprintf(presult, "Find %s found %s payload %d with mge_errno "
			"%d\n", node6.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Find %s found %s with mge_errno %d\n",
			node6.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	struct testnode node7;
	strcpy(node7.key, "zzz");
	pnode = find_bst_node(tree, &node7);
	if (pnode)
		sprintf(presult, "Find %s found %s payload %d with mge_errno "
			"%d\n", node7.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Find %s found %s with mge_errno %d\n",
			node7.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	fclose(fp);

	status = cmpresfile("./Test02Result.txt", "./Test02Answer.txt");

	tree = del_bst(tree);

	if (!status)
		printf("Test 2 passed.\n");
	else
		printf("Test 2 failed.\n");

	return status;
}

/*
 * Test 3.
 * Test the get counter function.
 */
int testget_counter_bst_node(void)
{
	char result[500] = { '\0' };
	char *presult = result;
	struct bstree *tree = NULL;
	struct bstree *res;
	struct testnode node1;
	struct testnode test;
	int status = 0, status1 = 0;
	int count;
	FILE *fp;

	tree = pop_tree(tree, BST_NODES_DUPLICATES);
	if (tree == NULL) {
		if (verbose)
			printf("Populate binary search tree failed.\n");
		return 1;
	}

	strcpy(test.key, "this");
	test.payload = 99;
	res = add_bst_node(tree, &test, sizeof test);
	if (res == NULL) {
		if (verbose)
			printf("%s\n", mge_strerror(mge_errno));
		del_bst(tree);
		return 1;
	}
	tree = res;
	if (verbose)
		printf("Add word - %s\n", test.key);

	if ((fp = fopen("./Test03aResult.txt", "w")) == NULL) {
		printf("Cannot create result file.\n");
		return 1;
	}


	strcpy(node1.key, "give");
	count = get_counter_bst_node(tree, &node1);
	sprintf(presult, "%s found %d times with mge_errno %d\n", node1.key,
		count, mge_errno);
	fputs(result, fp);
	if (verbose)
		printf("%s", presult);

	if (count < 0) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	strcpy(node1.key, "zzzz");
	count = get_counter_bst_node(tree, &node1);
	sprintf(presult, "%s found %d times with mge_errno %d\n", node1.key,
		count, mge_errno);
	fputs(result, fp);
	if (verbose)
		printf("%s", presult);

	if (count < 0) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	strcpy(node1.key, "aaaa");
	count = get_counter_bst_node(tree, &node1);
	sprintf(presult, "%s found %d times with mge_errno %d\n", node1.key,
		count, mge_errno);
	fputs(result, fp);
	if (verbose)
		printf("%s", presult);

	if (count < 0) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	strcpy(node1.key, "this");
	count = get_counter_bst_node(tree, &node1);
	sprintf(presult, "%s found %d times with mge_errno %d\n", node1.key,
		count, mge_errno);
	fputs(result, fp);
	if (verbose)
		printf("%s", presult);

	if (count < 0) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}

	fclose(fp);

	status = cmpresfile("./Test03aResult.txt", "./Test03aAnswer.txt");

	if (!status)
		printf("Test 3a passed.\n");
	else
		printf("Test 3a failed.\n");


	/* Now compare the resulting tree. */
	if ((fp = fopen("./Test03bResult.txt", "w")) == NULL) {
		printf("Cannot create result file.\n");
		return 1;
	}
	memset(presult, '\0', sizeof(result));
	presult = printtree(tree, presult);
	fputs(result, fp);
	fclose(fp);

	status1 = cmpresfile("./Test03bResult.txt", "./Test03bAnswer.txt");

	tree = del_bst(tree);

	if (!status1)
		printf("Test 3b passed.\n");
	else
		printf("Test 3b failed.\n");

	return (status ? status : status1);;
}
/*
 * Test 4.
 * Test find next function.
 */
int testfind_next_bst_node(void)
{
	char result[500] = { '\0' };
	char *presult = result;
	struct bstree *tree = NULL;
	struct testnode *pnode;
	struct testnode node2;
	int status = 0;
	FILE *fp;

	tree = pop_tree(tree, BST_NODES_UNIQUE);
	if (tree == NULL) {
		if (verbose)
			printf("Populate binary search tree failed.\n");
		return 1;
	}

	if ((fp = fopen("./Test04Result.txt", "w")) == NULL) {
		printf("Cannot create result file.\n");
		return 1;
	}


	strcpy(node2.key, "aa");
	pnode = find_next_bst_node(tree, &node2);
	if (pnode)
		sprintf(presult, "Next found after %s is %s payload %d & "
			"mge_errno %d\n", node2.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Next found after %s is %s & mge_errno %d\n",
			node2.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	struct testnode node3;
	strcpy(node3.key, "all");
	pnode = find_next_bst_node(tree, &node3);
	if (pnode)
		sprintf(presult, "Next found after %s is %s payload %d & "
			"mge_errno %d\n", node3.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Next found after %s is %s & mge_errno %d\n",
			node3.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	struct testnode node4;
	strcpy(node4.key, "give");
	pnode = find_next_bst_node(tree, &node4);
	if (pnode)
		sprintf(presult, "Next found after %s is %s payload %d & "
			"mge_errno %d\n", node4.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Next found after %s is %s & mge_errno %d\n",
			node4.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	struct testnode node5;
	strcpy(node5.key, "this");
	pnode = find_next_bst_node(tree, &node5);
	if (pnode)
		sprintf(presult, "Next found after %s is %s payload %d & "
			"mge_errno %d\n", node5.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Next found after %s is %s & mge_errno %d\n",
			node5.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	struct testnode node6;
	strcpy(node6.key, "us");
	pnode = find_next_bst_node(tree, &node6);
	if (pnode)
		sprintf(presult,"Next found after %s is %s payload %d & "
			"mge_errno %d\n", node6.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Next found after %s is %s & mge_errno %d\n",
			node6.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	struct testnode node7;
	strcpy(node7.key, "zzz");
	pnode = find_next_bst_node(tree, &node7);
	if (pnode)
		sprintf(presult, "Next found after %s is %s payload %d & "
			"mge_errno %d\n", node7.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Next found after %s is %s & mge_errno %d\n",
			node7.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	fclose(fp);

	status = cmpresfile("./Test04Result.txt", "./Test04Answer.txt");

	tree = del_bst(tree);

	if (!status)
		printf("Test 4 passed.\n");
	else
		printf("Test 4 failed.\n");

	return status;
}
/*
 * Test 5.
 * Test find previous function.
 */
int testfind_prev_bst_node(void)
{
	char result[500] = { '\0' };
	char *presult = result;
	struct bstree *tree = NULL;
	struct testnode *pnode;
	struct testnode node2;
	int status = 0;
	FILE *fp;

	tree = pop_tree(tree, BST_NODES_UNIQUE);
	if (tree == NULL) {
		if (verbose)
			printf("Populate binary search tree failed.\n");
		return 1;
	}

	if ((fp = fopen("./Test05Result.txt", "w")) == NULL) {
		printf("Cannot create result file.\n");
		return 1;
	}


	strcpy(node2.key, "aa");
	pnode = find_prev_bst_node(tree, &node2);
	if (pnode)
		sprintf(presult, "Prior found before %s is %s payload %d, "
			"mge_errno %d\n", node2.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Previous found before %s is %s with "
			"mge_errno %d\n", node2.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	struct testnode node3;
	strcpy(node3.key, "all");
	pnode = find_prev_bst_node(tree, &node3);
	if (pnode)
		sprintf(presult, "Prior found before %s is %s payload %d, "
			"mge_errno %d\n", node3.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Previous found before %s is %s with "
			"mge_errno %d\n", node3.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	struct testnode node4;
	strcpy(node4.key, "ask");
	pnode = find_prev_bst_node(tree, &node4);
	if (pnode)
		sprintf(presult, "Prior found before %s is %s payload %d, "
			"mge_errno %d\n", node4.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Previous found before %s is %s with "
			"mge_errno %d\n", node4.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	struct testnode node5;
	strcpy(node5.key, "give");
	pnode = find_prev_bst_node(tree, &node5);
	if (pnode)
		sprintf(presult, "Prior found before %s is %s payload %d, "
			"mge_errno %d\n", node5.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Previous found before %s is %s with "
			"mge_errno %d\n", node5.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	struct testnode node6;
	strcpy(node6.key, "i");
	pnode = find_prev_bst_node(tree, &node6);
	if (pnode)
		sprintf(presult, "Prior found before %s is %s payload %d, "
			"mge_errno %d\n", node6.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Previous found before %s is %s with "
			"mge_errno %d\n", node6.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	struct testnode node7;
	strcpy(node7.key, "us");
	pnode = find_prev_bst_node(tree, &node7);
	if (pnode)
		sprintf(presult, "Prior found before %s is %s payload %d, "
			"mge_errno %d\n", node7.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Previous found before %s is %s with "
			"mge_errno %d\n", node7.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	struct testnode node8;
	strcpy(node8.key, "zzz");
	pnode = find_prev_bst_node(tree, &node8);
	if (pnode)
		sprintf(presult, "Prior found before %s is %s payload %d, "
			"mge_errno %d\n", node8.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Previous found before %s is %s with "
			"mge_errno %d\n", node8.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	fclose(fp);

	status = cmpresfile("./Test05Result.txt", "./Test05Answer.txt");

	tree = del_bst(tree);

	if (!status)
		printf("Test 5 passed.\n");
	else
		printf("Test 5 failed.\n");

	return status;
}
/*
 * Test 6.
 * Test update node function.
 */
int testupd_bst_node(void)
{
	char result[500] = { '\0' };
	char *presult = result;
	struct bstree *tree = NULL;
	struct testnode *pnode;
	struct testnode node;
	int status = 0;
	FILE *fp;

	tree = pop_tree(tree, BST_NODES_UNIQUE);
	if (tree == NULL) {
		if (verbose)
			printf("Populate binary search tree failed.\n");
		return 1;
	}

	if ((fp = fopen("./Test06Result.txt", "w")) == NULL) {
		printf("Cannot create result file.\n");
		return 1;
	}


	strcpy(node.key, "NULL root");
	pnode = find_bst_node(NULL, &node);
	if (pnode)
		sprintf(presult, "Find %s found %s payload %d, mge_errno %d\n",
			node.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Find %s found %s with mge_errno %d\n",
			node.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}
	node.payload = 999;
	pnode = upd_bst_node(NULL, &node, sizeof node);
	if (pnode)
		sprintf(presult, "Update %s found %s payload %d with mge_errno "
			"%d\n", node.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Update %s found %s with mge_errno %d\n",
			node.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	strcpy(node.key, "NULL updobj");
	pnode = find_bst_node(tree, NULL);
	if (pnode)
		sprintf(presult, "Find %s found %s payload %d, mge_errno %d\n",
			node.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Find %s found %s with mge_errno %d\n",
			node.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}
	node.payload = 999;
	pnode = upd_bst_node(tree, NULL, sizeof node);
	if (pnode)
		sprintf(presult, "Update %s found %s payload %d with mge_errno "
			"%d\n", node.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Update %s found %s with mge_errno %d\n",
			node.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	strcpy(node.key, "zzzzz");
	pnode = find_bst_node(tree, &node);
	if (pnode)
		sprintf(presult, "Find %s found %s payload %d, mge_errno %d\n",
			node.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Find %s found %s with mge_errno %d\n",
			node.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}
	node.payload = 999;
	pnode = upd_bst_node(tree, &node, sizeof node);
	if (pnode)
		sprintf(presult, "Update %s found %s payload %d with mge_errno "
			"%d\n", node.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Update %s found %s with mge_errno %d\n",
			node.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}



	strcpy(node.key, "mask");
	pnode = find_bst_node(tree, &node);
	if (pnode)
		sprintf(presult, "Find %s found %s payload %d, mge_errno %d\n",
			node.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Find %s found %s with mge_errno %d\n",
			node.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}
	node.payload = 999;
	pnode = upd_bst_node(tree, &node, sizeof node);
	if (pnode)
		sprintf(presult, "Update %s found %s payload %d with mge_errno "
			"%d\n", node.key, pnode->key, pnode->payload,
			mge_errno);
	else
		sprintf(presult, "Update %s found %s with mge_errno %d\n",
			node.key, pnode->key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if ((pnode == NULL) && mge_errno) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	fclose(fp);

	status = cmpresfile("./Test06Result.txt", "./Test06Answer.txt");

	tree = del_bst(tree);

	if (!status)
		printf("Test 6 passed.\n");
	else
		printf("Test 6 failed.\n");

	return status;
}

/*
 * Test 7.
 * Test delete node.
 */
int testdel_bst_node(void)
{
	char result[500] = { '\0' };
	char *presult = result;
	struct bstree *tree = NULL;
	struct bstree *res;
	struct testnode node;
	int status = 0, status1 = 0;
	FILE *fp;

	tree = pop_tree(tree, BST_NODES_DUPLICATES);
	if (tree == NULL) {
		if (verbose)
			printf("Populate binary search tree failed.\n");
		return 1;
	}


	if ((fp = fopen("./Test07aResult.txt", "w")) == NULL) {
		printf("Cannot create result file.\n");
		return 1;
	}


	/* First add the word to give a fully populated parent. */
	strcpy(node.key, "twin");
	node.payload = 99;
	res = add_bst_node(tree, &node, sizeof node);
	if (res == NULL) {
		if (verbose)
			printf("%s\n", mge_strerror(mge_errno));
		del_bst(tree);
		return 1;
	}
	tree = res;
	if (verbose)
		printf("Add word - %s\n", node.key);

	sprintf(presult, "Node %s added with mge_errno %d\n",
			node.key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);



	/* Now delete that parent. */
	strcpy(node.key, "this");
	if (verbose)
		printf("Delete %s\n", node.key);

	res = del_bst_node(tree, &node);

	if (res)
		sprintf(presult, "Node %s deleted with mge_errno %d\n",
			node.key, mge_errno);
	else
		sprintf(presult, "Delete of %s attempted with mge_errno %d\n",
			node.key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if (res == NULL) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}
	else {
		tree = res;
	}


	strcpy(node.key, "Harry");
	if (verbose)
		printf("Delete %s\n", node.key);

	res = del_bst_node(tree, &node);

	if (res)
		sprintf(presult, "Node %s deleted with mge_errno %d\n",
			node.key, mge_errno);
	else
		sprintf(presult, "Delete of %s attempted with mge_errno %d\n",
			node.key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if (res == NULL) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}
	else {
		tree = res;
	}


	strcpy(node.key, "consistency");
	if (verbose)
		printf("Delete root node %s\n", node.key);

	res = del_bst_node(tree, &node);

	if (res)
		sprintf(presult, "Root node %s deleted with mge_errno %d\n",
			node.key, mge_errno);
	else
		sprintf(presult, "Delete of root node %s attempted with "
			"mge_errno %d\n", node.key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if (res == NULL) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}
	else {
		tree = res;
	}


	fclose(fp);

	status = cmpresfile("./Test07aResult.txt", "./Test07aAnswer.txt");

	if (!status)
		printf("Test 7a passed.\n");
	else
		printf("Test 7a failed.\n");


	/* Now compare the resulting tree. */
	if ((fp = fopen("./Test07bResult.txt", "w")) == NULL) {
		printf("Cannot create result file.\n");
		return 1;
	}
	memset(presult, '\0', sizeof(result));
	presult = printtree(tree, presult);
	fputs(result, fp);
	fclose(fp);

	status1 = cmpresfile("./Test07bResult.txt", "./Test07bAnswer.txt");

	tree = del_bst(tree);

	if (!status1)
		printf("Test 7b passed.\n");
	else
		printf("Test 7b failed.\n");

	return (status ? status : status1);
}

/*
 * Test 8.
 * Test delete of only node in tree.
 */
int testdelonlynode(void)
{
	char result[500] = { '\0' };
	char *presult = result;
	struct bstree *tree = NULL;
	struct bstree *res;
	struct testnode node;
	int status = 0;
	FILE *fp;

	tree = cre_bst(BST_NODES_UNIQUE,
			(int (*)(const void *, const void *))nodecmp);
	if (tree == NULL) {
		if (verbose)
			printf("Create binary search tree failed.\n");
		return 1;
	}


	if ((fp = fopen("./Test08Result.txt", "w")) == NULL) {
		printf("Cannot create result file.\n");
		return 1;
	}


	/* First add the word to give a count of 2. */
	strcpy(node.key, "mark");
	res = add_bst_node(tree, &node, sizeof node);
	if (res == NULL) {
		if (verbose)
			printf("%s\n", mge_strerror(mge_errno));
		del_bst(tree);
		return 1;
	}
	tree = res;
	if (verbose)
		printf("Add word - %s\n", node.key);

	sprintf(presult, "Node %s added with mge_errno %d\n",
			node.key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);


	/* Now delete that solitary node. */
	if (verbose)
		printf("Delete %s\n", node.key);

	res = del_bst_node(tree, &node);

	if (res == NULL)
		sprintf(presult, "Delete of %s attempted with mge_errno %d\n",
			node.key, mge_errno);
	else
		sprintf(presult, "Node %s deleted with mge_errno %d\n",
			node.key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if (res == NULL) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}
	else {
		tree = res;
	}


	fclose(fp);

	status = cmpresfile("./Test08Result.txt", "./Test08Answer.txt");

	if (!status)
		printf("Test 8 passed.\n");
	else
		printf("Test 8 failed.\n");

	tree = del_bst(tree);

	return status;
}

/*
 * Test 9.
 * Test delete of a duplicate node.
 */
int testdeldupnode(void)
{
	char result[500] = { '\0' };
	char *presult = result;
	struct bstree *tree = NULL;
	struct bstree *res;
	struct testnode node;
	int status = 0;
	int count;
	FILE *fp;

	tree = pop_tree(tree, BST_NODES_DUPLICATES);
	if (tree == NULL) {
		if (verbose)
			printf("Populate binary search tree failed.\n");
		return 1;
	}


	if ((fp = fopen("./Test09Result.txt", "w")) == NULL) {
		printf("Cannot create result file.\n");
		return 1;
	}


	/* First add the word to give a count of 2. */
	strcpy(node.key, "give");
	res = add_bst_node(tree, &node, sizeof node);
	if (res == NULL) {
		if (verbose)
			printf("%s\n", mge_strerror(mge_errno));
		del_bst(tree);
		return 1;
	}
	tree = res;
	if (verbose)
		printf("Add word - %s\n", node.key);

	sprintf(presult, "Node %s added with mge_errno %d\n",
			node.key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);


	count = get_counter_bst_node(tree, &node);
	sprintf(presult, "%s found %d times with mge_errno %d\n", node.key,
		count, mge_errno);
	fputs(result, fp);
	if (verbose)
		printf("%s", presult);

	if (count < 0) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	/* Now delete that duplicate node. */
	if (verbose)
		printf("Delete %s\n", node.key);

	res = del_bst_node(tree, &node);

	if (res)
		sprintf(presult, "Node %s deleted with mge_errno %d\n",
			node.key, mge_errno);
	else
		sprintf(presult, "Delete of %s attempted with mge_errno %d\n",
			node.key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if (res == NULL) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}
	else {
		tree = res;
	}


	count = get_counter_bst_node(tree, &node);
	sprintf(presult, "%s found %d times with mge_errno %d\n", node.key,
		count, mge_errno);
	fputs(result, fp);
	if (verbose)
		printf("%s", presult);

	if (count < 0) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}


	fclose(fp);

	status = cmpresfile("./Test09Result.txt", "./Test09Answer.txt");

	if (!status)
		printf("Test 9 passed.\n");
	else
		printf("Test 9 failed.\n");

	tree = del_bst(tree);

	return status;
}

/*
 * Test 10.
 * Test attempt to add duplicate to unique tree.
 */
int testaddduptounique(void)
{
	char result[500] = { '\0' };
	char *presult = result;
	struct bstree *tree = NULL;
	struct bstree *res;
	struct testnode node;
	int status = 0;
	FILE *fp;

	tree = pop_tree(tree, BST_NODES_UNIQUE);
	if (tree == NULL) {
		if (verbose)
			printf("Populate binary search tree failed.\n");
		return 1;
	}


	if ((fp = fopen("./Test10Result.txt", "w")) == NULL) {
		printf("Cannot create result file.\n");
		return 1;
	}


	/* Attempt add tof duplicate word. */
	strcpy(node.key, "give");
	res = add_bst_node(tree, &node, sizeof node);

	if (verbose)
		printf("Add word - %s\n", node.key);

	sprintf(presult, "Node ptr %p word %s add attempt with mge_errno %d\n",
		res, node.key, mge_errno);
	fputs(result, fp);

	if (verbose)
		printf("%s", presult);

	if (res == NULL) {
		sprintf(presult, "%s\n", mge_strerror(mge_errno));
		fputs(result, fp);
		if (verbose)
			printf("%s", presult);
	}
	else {
		tree = res;
	}


	fclose(fp);

	status = cmpresfile("./Test10Result.txt", "./Test10Answer.txt");

	if (!status)
		printf("Test 10 passed.\n");
	else
		printf("Test 10 failed.\n");

	tree = del_bst(tree);

	return status;
}
