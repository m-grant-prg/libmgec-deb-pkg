/* **********************************************************************
 *									*
 * Source: main.c							*
 * Author Copyright (C) 2017-2019  Mark Grant				*
 *									*
 * Purpose:								*
 *	Test program for error descriptions in libmgec shared library.	*
 * 									*
 * 									*
 * Released under the GPLv3 only.					*
 * SPDX-License-Identifier: GPL-3.0					*
 *									*
 ************************************************************************
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>

#include <mge-errno.h>


extern const size_t errno_desc_size;	/* Need this for testing */


/*
 * mge_errno test program.
 */
int main(int argc, char** argv)
{
	int i;

	/* For when mge_errno says look at errno */
	sav_errno = ENOMEM;

	printf("The error descriptions are:-\n\n");

	for ( i = 0; i < (int) errno_desc_size; i++)
		printf("%i\t%s\n", i, mge_strerror(i));

	/* For when mge_errno says look at gai_strerror */
	sav_errno = EAI_BADFLAGS;

	printf("\n\nThe error descriptions are:-\n\n");

	for ( i = 0; i < (int) errno_desc_size; i++)
		printf("%i\t%s\n", i, mge_strerror(i));

	printf("errno_desc has %i elements.\n", (int) errno_desc_size);

	printf("mge_errno %i gives message - %s\n", 0, mge_strerror(0));

	printf("mge_errno %i gives message - %s\n", -1, mge_strerror(-1));

	printf("mge_errno %i gives message - %s\n", 100, mge_strerror(100));
}
