#########################################################################
#									#
# Script ID: src/prg/c/src/test-bstree/Makefile.am			#
# Author: Copyright (C) 2015-2019  Mark Grant				#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0					#
#									#
# Purpose:								#
#	AutoMake script file to generate bstree test program.		#
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
# 13/01/2017	MG	1.0.4	Set debug or normal compile flags here.	#
# 25/03/2017	MG	1.0.5	Add temporary header directory.		#
# 03/04/2017	MG	1.0.6	Add Test answer files.			#
# 27/10/2017	MG	1.0.7	Change to use _LDADD for temporary	#
#				libraries as passing -L and the temp	#
#				directory does not necessarily leave	#
#				LD_LIBRARY_PATH in the correct order.	#
#				Re-order into logical steps.		#
# 10/12/2017	MG	1.0.8	Add SPDX license tags to source files.	#
# 02/01/2018	MG	1.0.9	Move to new source directory structure.	#
# 09/01/2018	MG	1.0.10	Correct usage of config.h		#
# 04/07/2018	MG	1.0.11	Improve debug flags used. Use gdb	#
#				orientated level 3 (includes		#
#				pre-processor macros).			#
# 10/05/2019	MG	1.0.12	Remove shebang.				#
#				Merge into one project.			#
#									#
#########################################################################


AM_CPPFLAGS = -I$(srcdir)/../../inc-tmp -I$(srcdir)/../../inc
AM_CPPFLAGS += -I../../gen/inc -I../../gen/lib


AM_CFLAGS = -Wall

if DEBUG
AM_CFLAGS += -ggdb3 -Og
else
AM_CFLAGS += -O2
endif


noinst_PROGRAMS = bstreetest
bstreetest_SOURCES = main.c


LDADD = ../libmgec/libmgec.la
LDADD += $(tmplibraries)


Test00StartingBSTree.txt Test01Answer.txt Test02Answer.txt Test03aAnswer.txt \
	Test03bAnswer.txt Test03ResultBSTree.txt Test04Answer.txt \
	Test05Answer.txt Test06Answer.txt Test07aAnswer.txt Test07bAnswer.txt \
	Test07ResultBSTree.txt Test08Answer.txt Test09Answer.txt \
	Test10Answer.txt:Makefile
	mkdir -p $(@D)
	rm -f $@ $@.tmp
	test -f ./$@.in || srcdir=$(srcdir)/; \
	cp $${srcdir}$(@F).in  $@

Test00StartingBSTree.txt: $(srcdir)/Test00StartingBSTree.txt.in
Test01Answer.txt: $(srcdir)/Test01Answer.txt.in
Test02Answer.txt: $(srcdir)/Test02Answer.txt.in
Test03aAnswer.txt: $(srcdir)/Test03aAnswer.txt.in
Test03bAnswer.txt: $(srcdir)/Test03bAnswer.txt.in
Test03ResultBSTree.txt: $(srcdir)/Test03ResultBSTree.txt.in
Test04Answer.txt: $(srcdir)/Test04Answer.txt.in
Test05Answer.txt: $(srcdir)/Test05Answer.txt.in
Test06Answer.txt: $(srcdir)/Test06Answer.txt.in
Test07aAnswer.txt: $(srcdir)/Test07aAnswer.txt.in
Test07bAnswer.txt: $(srcdir)/Test07bAnswer.txt.in
Test07ResultBSTree.txt: $(srcdir)/Test07ResultBSTree.txt.in
Test08Answer.txt: $(srcdir)/Test08Answer.txt.in
Test09Answer.txt: $(srcdir)/Test09Answer.txt.in
Test10Answer.txt: $(srcdir)/Test10Answer.txt.in

noinst_DATA = Test00StartingBSTree.txt Test01Answer.txt Test02Answer.txt \
	Test03aAnswer.txt Test03bAnswer.txt Test03ResultBSTree.txt \
	Test04Answer.txt Test05Answer.txt Test06Answer.txt Test07aAnswer.txt \
	Test07bAnswer.txt Test07ResultBSTree.txt Test08Answer.txt \
	Test09Answer.txt Test10Answer.txt

EXTRA_DIST = $(srcdir)/Test00StartingBSTree.txt.in \
	$(srcdir)/Test01Answer.txt.in $(srcdir)/Test02Answer.txt.in \
	$(srcdir)/Test03aAnswer.txt.in $(srcdir)/Test03bAnswer.txt.in \
	$(srcdir)/Test03ResultBSTree.txt.in $(srcdir)/Test04Answer.txt.in \
	$(srcdir)/Test05Answer.txt.in $(srcdir)/Test06Answer.txt.in \
	$(srcdir)/Test07aAnswer.txt.in $(srcdir)/Test07bAnswer.txt.in \
	$(srcdir)/Test07ResultBSTree.txt.in $(srcdir)/Test08Answer.txt.in \
	$(srcdir)/Test09Answer.txt.in $(srcdir)/Test10Answer.txt.in

CLEANFILES = *.tmp *.txt
