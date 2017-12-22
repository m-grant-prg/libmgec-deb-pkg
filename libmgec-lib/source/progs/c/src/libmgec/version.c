/**
 * @file libmgec-lib/source/progs/c/src/libmgec/version.c
 *
 * Standard versioning.
 *
 * Standard library-wide software versioning functions and information.
 *
 * @author Copyright (C) 2015-2017  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0
 *
 * @version _v1.1.2 ==== 09/11/2017_
 */

/* **********************************************************************
 *									*
 * Changelog								*
 *									*
 * Date		Author	Version	Description				*
 *									*
 * 07/08/2015	MG	1.0.1	First release.				*
 * 11/08/2015	MG	1.0.2	Add functions delnode() & freenode().	*
 * 18/09/2015	MG	1.0.3	Change function names to XXX_bt_node().	*
 *				Change find_bt_node() to		*
 *				get_counter_bt_node() as it returns the	*
 *				count.					*
 *				Add find_bt_node(), upd_bt_node().	*
 *				Change free_btree() to return NULL.	*
 *				Add unique flag to add_bt_node().	*
 *				Improve overall use of btree_errno.	*
 *				Modify del_bt_node() to decrement the	*
 *				node counter instead of deleting the	*
 *				node if the counter is > 1, (i.e.	*
 *				duplicates are allowed).		*
 *				Add function parameter checking.	*
 *				Change defined flags and errors to be	*
 *				easily identifiable as btree elements.	*
 * 03/11/2015	MG	1.0.4	Change from bt and btree names to bst	*
 *				and bstree as this is a binary search	*
 *				tree, not a b-tree.			*
 * 11/11/2015	MG	1.0.5	Change for extraction of bstree.h from	*
 *				now umbrella listsandsorts.h.		*
 *				Add support for singly linked lists.	*
 *				Elevate errno defs to listsandsorts.h.	*
 *				Add base.c for common functions and	*
 *				definitions.				*
 * 02/05/2016	MG	1.0.6	Add singly linked list functionality.	*
 * 06/05/2016	MG	1.0.7	Add doubly linked list functionality.	*
 * 16/07/2016	MG	1.0.8	Move towards kernel coding style.	*
 * 17/07/2016	MG	1.0.9	Further coding style change.		*
 * 12/03/2017	MG	1.0.10	get_counter_bst_node() now returns -1	*
 *				on error.				*
 * 03/05/2017	MG	1.1.0	Return NULL pointer, -1 or error number	*
 *				when possible on error.			*
 *				Apply coding standards from template	*
 *				atclstv v1.0.0				*
 *				Add buffer, message and memory		*
 *				functions.				*
 *				Introduce library-wide mge_errno	*
 *				variable and error handling.		*
 *				Add bst trace function to provide node	*
 *				coordinates.				*
 *				Add exhaustive bstree tests.		*
 *				Introduce concept and support for a	*
 *				discreet bst object.			*
 * 05/11/2017	MG	1.1.1	Add SSH error message.			*
 * 				Add Doxygen comments.			*
 * 09/11/2017	MG	1.1.2	Add SPDX license tags.			*
 *									*
 ************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <libmgec.h>
#include <config.h>

/** The source code version. */
#define SOURCE_VERSION "1.1.2"

/**
 * Get the git-describe based package version.
 * @return The package version string.
 */
char *libmgec_get_pkg_version(void)
{
	return PACKAGE_VERSION;
}

/**
 * Get the source version.
 * @return The source version string.
 */
char *libmgec_get_src_version(void)
{
	return SOURCE_VERSION;
}

/**
 * Print the package version string to stdout.
 */
void libmgec_print_pkg_version(void)
{
	printf("%s %s %s", "libmgec Package version -", PACKAGE_VERSION, "\n");
}

/**
 * Print the source version string to stdout.
 */
void libmgec_print_src_version(void)
{
	printf("%s %s %s", "libmgec Source version -", SOURCE_VERSION, "\n");
}
