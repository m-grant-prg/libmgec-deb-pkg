#! /usr/bin/env bash
#########################################################################
#									#
# Script ID: libmgec-lib/source/progs/c/src/libmgec/Makefile.am		#
# Author: Copyright (C) 2015-2017  Mark Grant				#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0					#
#									#
# Purpose:								#
#	AutoMake script file to generate libmgec library from source.	#
#									#
#########################################################################

#########################################################################
#									#
# Changelog								#
#									#
# Date		Author	Version	Description				#
#									#
# 07/08/2015	MG	1.0.1	First release.				#
# 25/10/2015	MG	1.0.2	Restructure and change to conform to	#
#				AutoTools General Template v1.0.6.	#
# 03/11/2015	MG	1.0.3	Change from bt and btree names to bst	#
#				and bstree as this is a binary search	#
#				tree, not a b-tree.			#
# 07/11/2015	MG	1.0.4	Include base.c build.			#
# 02/05/2016	MG	1.0.5	Add Singly Linked List functionality.	#
# 06/05/2016	MG	1.0.6	Add Doubly Linked List functionality.	#
# 15/11/2016	MG	1.0.7	Add buffer, message and memory sources.	#
# 13/01/2017	MG	1.0.8	Set debug or normal compile flags here.	#
# 24/01/2017	MG	1.0.9	Change for new source directory		#
#				structure and new error sources.	#
#				Remove un-needed base.c.		#
# 25/03/2017	MG	1.0.10	Add temporary header directory.		#
# 09/06/2017	MG	1.0.11	Add support for temporary libraries.	#
# 27/10/2017	MG	1.0.12	Change to use _LIBADD for temporary	#
#				libraries as passing -L and the temp	#
#				directory does not necessarily leave	#
#				LD_LIBRARY_PATH in the correct order.	#
#				Re-order into logical steps.		#
# 10/12/2017	MG	1.0.13	Add SPDX license tags to source files.	#
#									#
#########################################################################


AM_CPPFLAGS = -I$(srcdir)/../../inc-tmp -I$(srcdir)/../../inc
AM_CPPFLAGS += -I$(top_srcdir)/../libmgec-dev/source/progs/c/inc
AM_CPPFLAGS += -I../../sysgen/lib


AM_CFLAGS = -Wall

if DEBUG
AM_CFLAGS += -g -Og
else
AM_CFLAGS += -O2
endif


noinst_HEADERS = listsandsorts/internal.h


lib_LTLIBRARIES = libmgec.la

libmgec_la_SOURCES = buf-msg/buffer.c buf-msg/message.c
libmgec_la_SOURCES += errors/errno.c errors/error.c
libmgec_la_SOURCES += listsandsorts/bstree.c listsandsorts/dllist.c
libmgec_la_SOURCES += listsandsorts/sllist.c
libmgec_la_SOURCES += memory/memory.c
libmgec_la_SOURCES += version.c


AM_LDFLAGS = -version-info 0:0:0


libmgec_la_LIBADD = $(tmplibraries)
