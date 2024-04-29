/**
 * @file src/prg/c/inc/libmgec/mge-errno.h
 *
 * Details for mge_errno system.
 *
 * Specification of mge_errno values and all mge_errno related information.
 *
 * @author Copyright (C) 2017-2023  Mark Grant
 *
 * Released under the GPLv3 only.\n
 * SPDX-License-Identifier: GPL-3.0-only
 *
 * @version _v1.1.0 ==== 02/11/2023_
 */

#ifndef MGE_ERRNO_H
#define MGE_ERRNO_H

#include <sys/types.h>

#include <libmgec/mge-portability.h>

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
#define MGE_PROTO 14	      /**< Protocol error. */
#define MGE_GENERAL 15	      /**< General error. */

const char *mge_strerror(const int mge_err);

END_C_DECLS

#endif /* ndef MGE_ERRNO_H */
