/*
 * Source: sllisttest.h
 *
 * Singly linked list test header file.
 *
 * Header file for testing singly linked lists in the libmgec shared library.
 *
 * Author Copyright (C) 2019, 2021, 2022  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 */

#ifndef SLLISTTEST_H
#define SLLISTTEST_H

#include <libmgec/mge-portability.h>

#include <stddef.h>
#include <stdio.h>

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

int nodecmp(const void *node1, const void *node2);

int test01(void);

int test02(void);

int test03(void);

int test04(void);

int test05(void);

END_C_DECLS

#endif /* ndef SLLISTTEST_H */
