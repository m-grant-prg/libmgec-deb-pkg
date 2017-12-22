#! /usr/bin/env bash
#########################################################################
#									#
# Script ID: libmgec-dev/Makefile.am					#
# Author: Copyright (C) 2015-2017  Mark Grant				#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0					#
#									#
# Purpose:								#
#	AutoMake script file to generate libmgec-dev project from	#
# source.								#
#									#
#########################################################################

#########################################################################
#									#
# Changelog								#
#									#
# Date		Author	Version	Description				#
#									#
# 12/07/2015	MG	1.0.1	First release.				#
# 26/08/2015	MG	1.0.2	Add btree manual page subdir.		#
# 25/10/2015	MG	1.0.3	Restructure and change to conform to	#
#				AutoTools General Template v1.0.6.	#
# 03/11/2015	MG	1.0.4	Change from bt and btree names to bst	#
#				and bstree as this is a binary search	#
#				tree, not a b-tree.			#
# 03/05/2016	MG	1.0.5	Add single linked list man pages.	#
# 06/05/2016	MG	1.0.6	Add double linked list man pages.	#
# 31/12/2016	MG	1.0.7	Add memory, buffer and message man	#
#				pages.					#
# 24/01/2017	MG	1.0.8	Add errno man pages.			#
# 22/12/2017	MG	1.0.9	Add SPDX license tags to source files.	#
#									#
#########################################################################

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = source/man/man3/bstree source/man/man3/sllist source/man/man3/dllist
SUBDIRS += source/man/man3/buffer source/man/man3/errno
SUBDIRS += source/man/man3/memory source/man/man3/message
SUBDIRS += source/progs/c/inc source/progs/c/src
