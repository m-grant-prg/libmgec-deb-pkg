/**
 * @file src/prg/c/src/libmgec/version.c
 *
 * Standard versioning.
 *
 * Standard library-wide software versioning functions and information.
 *
 * @author Copyright (C) 2015-2019, 2021-2023  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.1.0 ==== 02/11/2023_
 */

#include <config.h>
#include <stdio.h>

#include <libmgec/libmgec.h>

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
