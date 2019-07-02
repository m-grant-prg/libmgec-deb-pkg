/*
 * Source: sllisttest.h
 *
 * Singly linked list test header file.
 *
 * Header file for testing singly linked lists in the libmgec shared library.
 *
 * Author Copyright (C) 2019  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0
 *
 */

#ifndef SLLISTTEST_H
#define SLLISTTEST_H

#include <portability.h>

BEGIN_C_DECLS

extern int verbose;

struct testnode {
	char key[20];
	int payload;
};

struct sllistnode *create_list(struct sllistnode *root);

char *printlist(struct sllistnode *root, char *output);

int cmpresfile(char *result, char *answer);

char *emit_outputs(char *pr, FILE *fp);

int test01(void);

int test02(void);

int test03(void);

int test04(void);

END_C_DECLS

#endif /* ndef SLLISTTEST_H */

