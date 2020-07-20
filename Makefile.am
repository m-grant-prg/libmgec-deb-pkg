#########################################################################
#									#
# Script ID: ./Makefile.am						#
# Author: Copyright (C) 2015-2020  Mark Grant				#
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
# 15/04/2018	MG	1.0.13	Add srctarball target to build a source	#
#				tarball in the build directory. Uses	#
#				git archive to archive HEAD.		#
# 08/06/2018	MG	1.0.14	Add info messages to srctarball target.	#
# 06/09/2018	MG	1.0.15	Add buffers and messages test program.	#
# 09/09/2018	MG	1.0.16	Add build for inc directory.		#
# 21/10/2018	MG	1.0.17	Change srctarball target to build with	#
#				src between package name and version in	#
#				filename.				#
# 10/02/2019	MG	1.0.18	Enable use of self-written m4 macros in	#
#				m4extra.				#
# 10/05/2019	MG	1.1.1	Remove shebang.				#
#				Make source tarball name == GitHub.	#
#				Add install of standard GNU files such	#
#				as AUTHORS etc.				#
#				Merge dev sub-project.			#
#				Merge doc sub-project.			#
# 17/06/2019	MG	1.1.2	Add directory to run make check tests.	#
# 28/06/2019	MG	1.1.3	To enable make distcheck to work, any	#
#				hard-coded paths requiring permissions	#
#				such as /etc or fixed locations such as	#
#				/usr/share/java must be accommodated,	#
#				so set the configure flags to be used	#
#				by make distcheck.			#
# 20/07/2020	MG	1.1.4	Merge buffer and message man pages.	#
#									#
#########################################################################

ACLOCAL_AMFLAGS = -I m4 -I m4extra


AM_DISTCHECK_CONFIGURE_FLAGS = --enable-distcheckfake=yes


SUBDIRS = src/man/3/bstree src/man/3/sllist src/man/3/dllist
SUBDIRS += src/man/3/buf-msg src/man/3/errno src/man/3/memory
SUBDIRS += src/prg/c/gen/lib
SUBDIRS += src/prg/c/inc
SUBDIRS += src/prg/c/inc-tmp
SUBDIRS += src/prg/c/lib-tmp
SUBDIRS += src/prg/c/pkg-config
SUBDIRS += src/prg/c/src/libmgec
SUBDIRS += src/prg/c/src/test-bstree
SUBDIRS += src/prg/c/src/test-buf-msg
SUBDIRS += src/prg/c/src/test-dllist
SUBDIRS += src/prg/c/src/test-errno
SUBDIRS += src/prg/c/src/test-sllist
SUBDIRS += src/prg/c/src/run-tests
SUBDIRS += doc/doxygen


doc_DATA = AUTHORS ChangeLog COPYING NEWS README


EXTRA_DIST = $(srcdir)/AUTHORS $(srcdir)/ChangeLog $(srcdir)/COPYING \
		$(srcdir)/NEWS $(srcdir)/README

EXTRA_DIST += m4/gnulib-cache.m4


srctarball:
	@cwd="$${PWD}" && \
	targ="$${cwd}/@PACKAGE_TARNAME@-@PACKAGE_VERSION@.tar.gz" && \
	cd @srcdir@ && \
	echo "making srctarball from @srcdir@" && \
	echo "GA	$${targ}" && \
	git archive --format=tar.gz \
		--prefix=@PACKAGE_TARNAME@-@PACKAGE_VERSION@/ \
		--output=$${targ} \
		HEAD && \
	cd -

