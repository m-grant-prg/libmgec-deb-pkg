/**
 * @file src/prg/c/inc/mge-errno.h
 *
 * Details for mge_errno system.
 *
 * Specification of mge_errno values and all mge_errno related information.
 *
 * @author Copyright (C) 2017-2021  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.0.13 ==== 03/12/2021_
 */

/* **********************************************************************
 *									*
 * Changelog								*
 *									*
 * Date		Author	Version	Description				*
 *									*
 * 23/01/2017	MG	1.0.1	First release.				*
 * 29/01/2017	MG	1.0.2	Add getaddrinfo related errors. Remove	*
 *				unnecessary _ERR suffix.		*
 * 03/02/2017	MG	1.0.3	Add config file errors.			*
 * 08/02/2017	MG	1.0.4	Add message errors.			*
 * 28/09/2017	MG	1.0.5	Add SSH error.				*
 * 04/11/2017	MG	1.0.6	Add Doxygen comments.			*
 * 09/11/2017	MG	1.0.7	Add SPDX license tag.			*
 * 02/01/2018	MG	1.0.8	Move to new source directory structure.	*
 * 31/01/2018	MG	1.0.9	Add Lock not found.			*
 * 17/05/2018	MG	1.0.10	Add Client blocked.			*
 * 08/06/2019	MG	1.0.11	clang-format coding style changes.	*
 * 12/03/2020	MG	1.0.12	Add identification error.		*
 * 03/12/2021	MG	1.0.13	Tighten SPDX tag.			*
 *									*
 ************************************************************************
 */

#ifndef MGE_ERRNO_H
#define MGE_ERRNO_H

#include <sys/types.h>

#include <portability.h>

BEGIN_C_DECLS

extern int mge_errno;
extern int sav_errno;

/* mge_errno values. */
#define MGE_ERRNO 1	      /**< Error is represented by errno. */
#define MGE_GAI 2	      /**< sav_errno holds the getaddrinfo error. */
#define MGE_GAI_BIND 3	      /**< Bind / Connect failed on GAI data. */
#define MGE_PARAM 4	      /**< Error in parameters passed. */
#define MGE_DUPLICATE_NODE 5  /**< Duplicate node found. */
#define MGE_NODE_NOT_FOUND 6  /**< Node not found. */
#define MGE_CONFIG_PARAM 7    /**< Invalid config file param. */
#define MGE_CONFIG_PARSE 8    /**< Cannot parse config file. */
#define MGE_INVAL_MSG 9	      /**< Invalid message received. */
#define MGE_SSH 10	      /**< SSH error. */
#define MGE_LOCK_NOT_FOUND 11 /**< Lock does not exist. */
#define MGE_CLIENT_BLOCKED 12 /**< Client is blocked on the server. */
#define MGE_ID 13	      /**< Identification error. */

const char *mge_strerror(const int mge_err);

END_C_DECLS

#endif /* ndef MGE_ERRNO_H */

