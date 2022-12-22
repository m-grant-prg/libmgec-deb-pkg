/* **********************************************************************
 *									*
 * Source: main.c							*
 * Author Copyright (C) 2018-2019, 2021  Mark Grant			*
 *									*
 * Purpose:								*
 *	Test program for buffers & messages in libmgec shared library.	*
 * 									*
 * 									*
 * Released under the GPLv3 only.					*
 * SPDX-License-Identifier: GPL-3.0-only				*
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
int main(void)
{
	struct mgebuffer buf = MGEBUFFER_INIT;
	struct mgemessage msg = MGEMESSAGE_INIT(';', ',');

	print_def_buf_values();
	print_buf(&buf);

	print_def_msg_values();
	print_msg(&msg);
}

