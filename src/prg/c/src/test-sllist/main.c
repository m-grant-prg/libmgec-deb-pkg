/* **********************************************************************
 *									*
 * Source: main.c							*
 * Author Copyright (C) 2017-2019, 2021, 2022  Mark Grant		*
 *									*
 * Purpose:								*
 *	Test program for singly linked lists in libmgec shared library.	*
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

int verbose;

/*
 * sllist test program.
 */
int main(int argc, char **argv)
{
	int i;
	int status = 0, status1 = 0;
	char choice[10] = { '\0' };
	char *pchoice = choice;

	printf("Choose one of :-\n");
	printf("0) Test 01 - Load with add_tail and free sllist.\n");
	printf("1) Test 01 - Load with add_tail and free sllist - verbose.\n");
	printf("2) Test 02 - Test parameter errors.\n");
	printf("3) Test 02 - Test parameter errors - verbose.\n");
	printf("4) Test 03 - Test find next node.\n");
	printf("5) Test 03 - Test find next node - verbose.\n");
	printf("6) Test 04 - Load with add_head and free sllist.\n");
	printf("7) Test 04 - Load with add_head and free sllist - verbose.\n");
	printf("8) Test 05 - Test find node.\n");
	printf("9) Test 05 - Test find node - verbose.\n");
	printf("y) Run all Tests.\n");
	printf("z) Run all Tests - verbose.\n");
	printf("\n[Choice]: ");

	/* If no args then run interactively, otherwise argv[1] is the choice */
	if (argc == 1) {
		i = scanf("%1s", choice);
		if (i != 1) {
			printf("Input error.\n");
			exit(1);
		}
	} else if (argc > 2) {
		printf("Input error.\n");
		exit(1);
	} else {
		choice[0] = *argv[1];
	}

	switch (*pchoice) {
	case '0':
		verbose = 0;
		status = test01();
		break;
	case '1':
		verbose = 1;
		status = test01();
		break;
	case '2':
		verbose = 0;
		status = test02();
		break;
	case '3':
		verbose = 1;
		status = test02();
		break;
	case '4':
		verbose = 0;
		status = test03();
		break;
	case '5':
		verbose = 1;
		status = test03();
		break;
	case '6':
		verbose = 0;
		status = test04();
		break;
	case '7':
		verbose = 1;
		status = test04();
		break;
	case '8':
		verbose = 0;
		status = test05();
		break;
	case '9':
		verbose = 1;
		status = test05();
		break;
	case 'y':
		verbose = 0;
		status1 = test01();
		if (status1)
			status = 1;
		status1 = test02();
		if (status1)
			status = 1;
		status1 = test03();
		if (status1)
			status = 1;
		status1 = test04();
		if (status1)
			status = 1;
		status1 = test05();
		if (status1)
			status = 1;
		break;
	case 'z':
		verbose = 1;
		status1 = test01();
		if (status1)
			status = 1;
		status1 = test02();
		if (status1)
			status = 1;
		status1 = test03();
		if (status1)
			status = 1;
		status1 = test04();
		if (status1)
			status = 1;
		status1 = test05();
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
