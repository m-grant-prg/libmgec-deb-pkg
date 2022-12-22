/**
 * @file src/prg/c/inc/portability.h
 *
 * Header file to ease portability.
 *
 * Includes suggestions from the GNU Libtools documentation.
 *
 * @author Copyright (C) 2015-2019, 2021  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.0.7 ==== 03/12/2021_
 */

/* **********************************************************************
 *									*
 * Changelog								*
 *									*
 * Date		Author	Version	Description				*
 *									*
 * 15/06/2015	MG	1.0.1	First release.				*
 * 16/07/2016	MG	1.0.2	Move towards kernel coding style.	*
 * 05/11/2017	MG	1.0.3	Add Doxygen comments.			*
 * 09/11/2017	MG	1.0.4	Add SPDX license tag.			*
 * 02/01/2018	MG	1.0.5	Move to new source directory structure.	*
 * 08/06/2019	MG	1.0.6	clang-format coding style changes.	*
 * 03/12/2021	MG	1.0.7	Tighten SPDX tag.			*
 *									*
 ************************************************************************
 */

#ifndef PORTABILITY_H
#define PORTABILITY_H

#undef BEGIN_C_DECLS
#undef END_C_DECLS

#ifdef __cplusplus
	#define BEGIN_C_DECLS extern "C" {
	#define END_C_DECLS }
#else
	/**
	 * BEGIN_C_DECLS should be used at the beginning of declarations so that
	 * C++ compilers don't mangle their names.
	 */
	#define BEGIN_C_DECLS
	/**
	 * Use END_C_DECLS at the end of C declarations.
	 */
	#define END_C_DECLS
#endif

#undef PARAMS

#if defined __STDC__ || defined _AIX                                  \
	|| (defined __mips && defined _SYSTYPE_SVR4) || defined WIN32 \
	|| defined __cplusplus
	#define PARAMS(protos) protos
#else
	/**
	 * PARAMS is a macro used to wrap function prototypes so that:-
	 * compilers that don't understand ANSI C prototypes still work,
	 * and, ANSI C compilers can issue warnings about type mismatches.
	 */
	#define PARAMS(protos) ()
#endif

#endif /* ndef PORTABILITY_H */

