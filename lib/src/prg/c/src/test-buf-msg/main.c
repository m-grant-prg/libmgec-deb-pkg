/* **********************************************************************
 *									*
 * Source: main.c							*
 * Author: Mark Grant							*
 *									*
 * Purpose:								*
 *	Test program for buffers & messages in libmgec shared library.	*
 * 									*
 * 									*
 * Released under the GPLv3 only.					*
 * SPDX-License-Identifier: GPL-3.0					*
 *									*
 ************************************************************************
 */

#include <stdio.h>
#include <stdbool.h>

#include <mgebuffer.h>
#include <mgemessage.h>


/*
 * buffers and messages test program.
 */
int main(int argc, char** argv)
{
	struct mgebuffer buf = MGEBUFFER_INIT;
	print_buf(&buf);

	struct mgemessage msg = MGEMESSAGE_INIT(';', ',');
	print_msg(&msg);
}
