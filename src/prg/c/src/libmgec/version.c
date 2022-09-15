/**
 * @file src/prg/c/src/libmgec/version.c
 *
 * Standard versioning.
 *
 * Standard library-wide software versioning functions and information.
 *
 * @author Copyright (C) 2015-2019, 2021, 2022  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.0.8 ==== 15/09/2022_
 */

/* **********************************************************************
 *									*
 * Changelog								*
 *									*
 * Date		Author	Version	Description				*
 *									*
 * 07/08/2015	MG	1.0.1	First release.				*
 * 09/11/2017	MG	1.0.2	Add SPDX license tags.			*
 * 02/01/2018	MG	1.0.3	Move to new source directory structure.	*
 * 04/06/2018	MG	1.0.4	Make this ChangeLog for this file only.	*
 * 20/06/2018	MG	1.0.5	Remove SOURCE_CODE define, now uses the	*
 *				AC_DEFINE'd value in config.h		*
 * 11/06/2019	MG	1.0.6	clang-format coding style changes.	*
 * 04/12/2021	MG	1.0.7	Tighten SPDX tag.			*
 * 15/09/2022	MG	1.0.8	Remove unnecessary header stdlib.h	*
 *									*
 ************************************************************************
 */

#include <config.h>
#include <stdio.h>

#include <libmgec.h>

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
