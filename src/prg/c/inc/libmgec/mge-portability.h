/**
 * @file src/prg/c/inc/libmgec/mge-portability.h
 *
 * Header file to ease portability.
 *
 * Includes suggestions from the GNU Libtools documentation.
 *
 * @author Copyright (C) 2015-2019, 2021-2023  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.1.0 ==== 02/11/2023_
 */

#ifndef MGE_PORTABILITY_H
#define MGE_PORTABILITY_H

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

#endif /* ndef MGE_PORTABILITY_H */
