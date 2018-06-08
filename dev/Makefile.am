#! /usr/bin/env bash
#########################################################################
#									#
# Script ID: dev/Makefile.am						#
# Author: Copyright (C) 2015-2018  Mark Grant				#
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
# 02/01/2018	MG	1.0.10	Move to new source directory structure.	#
# 15/04/2018	MG	1.0.11	Add srctarball target to build a source	#
#				tarball in the build directory. Uses	#
#				git archive to archive HEAD.		#
# 08/06/2018	MG	1.0.12	Add info messages to srctarball target.	#
#									#
#########################################################################

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = src/man/3/bstree src/man/3/sllist src/man/3/dllist
SUBDIRS += src/man/3/buffer src/man/3/errno
SUBDIRS += src/man/3/memory src/man/3/message
SUBDIRS += src/prg/c/inc src/prg/c/src


srctarball:
	@cwd="$${PWD}" && \
	cd @srcdir@ && \
	echo "making srctarball from @srcdir@" && \
	echo "GA	@builddir@/@PACKAGE_TARNAME@-@PACKAGE_VERSION@.tar.gz" \
	&& \
	git archive --format=tar.gz \
		--prefix=@PACKAGE_TARNAME@-@PACKAGE_VERSION@/ \
		--output=$${cwd}/@PACKAGE_TARNAME@-@PACKAGE_VERSION@.tar.gz \
		HEAD && \
	cd -
