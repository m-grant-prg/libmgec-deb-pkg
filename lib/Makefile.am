#! /usr/bin/env bash
#########################################################################
#									#
# Script ID: lib/Makefile.am						#
# Author: Copyright (C) 2015-2018  Mark Grant				#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0					#
#									#
# Purpose:								#
#	AutoMake script file to generate libmgec project from		#
# source.								#
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
# 02/05/2016	MG	1.0.4	Add build of sllist test suite.		#
# 02/05/2016	MG	1.0.5	Add build of dllist test suite.		#
# 22/01/2017	MG	1.0.6	Add build of errno test suite.		#
# 25/03/2017	MG	1.0.7	Add temporary header directory.		#
# 03/04/2017	MG	1.0.8	Add non-distribution header directory.	#
# 09/06/2017	MG	1.0.9	Add support for temporary libraries.	#
# 10/12/2017	MG	1.0.10	Add SPDX license tags to source files.	#
# 02/01/2018	MG	1.0.11	Move to new source directory structure.	#
# 09/01/2018	MG	1.0.12	Correct generation of config.h		#
#									#
#########################################################################

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = src/prg/c/gen/lib
SUBDIRS += src/prg/c/inc-tmp
SUBDIRS += src/prg/c/lib-tmp
SUBDIRS += src/prg/c/src/libmgec
SUBDIRS += src/prg/c/src/test-bstree
SUBDIRS += src/prg/c/src/test-dllist
SUBDIRS += src/prg/c/src/test-errno
SUBDIRS += src/prg/c/src/test-sllist

EXTRA_DIST  = m4/gnulib-cache.m4
