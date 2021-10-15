#########################################################################
#									#
# Script ID: src/prg/c/src/test-bstree/Makefile.am			#
# Author: Copyright (C) 2015-2019, 2021  Mark Grant			#
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
# 17/06/2019	MG	1.0.13	Change to use the check target.		#
# 25/07/2021	MG	1.0.14	Use CFLAGS prepared by configure.	#
#				Add conditional use Sparse CFLAGS.	#
# 26/07/2021	MG	1.0.15	Use CPPFLAGS prepared by configure.	#
#				Use LDFLAGS prepared by configure.	#
# 15/10/2021	MG	1.0.16	Change debug optimisation to -O0	#
#									#
#########################################################################


AM_CPPFLAGS = $(MG_CPPFLAGS)
AM_CPPFLAGS += -I$(srcdir)/../../inc-tmp -I$(srcdir)/../../inc
AM_CPPFLAGS += -I../../gen/inc -I../../gen/lib


AM_CFLAGS = $(MG_CFLAGS)
if DEBUG
AM_CFLAGS += -ggdb3 -O0
else
AM_CFLAGS += -O2
endif
if SPARSE
AM_CFLAGS += -Wsparse-all -Wno-vla
endif


check_PROGRAMS = bstreetest
bstreetest_SOURCES = main.c


AM_LDFLAGS = $(MG_LDFLAGS)


LDADD = ../libmgec/libmgec.la
LDADD += $(tmplibraries)


Test00StartingBSTree.txt Test01Answer.txt Test02Answer.txt Test03aAnswer.txt \
	Test03bAnswer.txt Test03ResultBSTree.txt Test04Answer.txt \
	Test05Answer.txt Test06Answer.txt Test07aAnswer.txt Test07bAnswer.txt \
	Test07ResultBSTree.txt Test08Answer.txt Test09Answer.txt \
	Test10Answer.txt: Makefile
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

check_DATA = Test00StartingBSTree.txt Test01Answer.txt Test02Answer.txt \
	Test03aAnswer.txt Test03bAnswer.txt Test03ResultBSTree.txt \
	Test04Answer.txt Test05Answer.txt Test06Answer.txt Test07aAnswer.txt \
	Test07bAnswer.txt Test07ResultBSTree.txt Test08Answer.txt \
	Test09Answer.txt Test10Answer.txt


bstreetest01b.sh bstreetest02d.sh bstreetest03f.sh bstreetest04h.sh \
	bstreetest05j.sh bstreetest06l.sh bstreetest07n.sh bstreetest08p.sh \
	bstreetest09r.sh bstreetest10t.sh: Makefile
	mkdir -p $(@D)
	rm -f $@ $@.tmp
	test -f ./$@.in || srcdir=$(srcdir)/; \
	$(edit) $${srcdir}$(@F).in > $@.tmp
	mv $@.tmp $@
	chmod a+x $@
bstreetest01b.sh: $(srcdir)/bstreetest01b.sh.in
bstreetest02d.sh: $(srcdir)/bstreetest02d.sh.in
bstreetest03f.sh: $(srcdir)/bstreetest03f.sh.in
bstreetest04h.sh: $(srcdir)/bstreetest04h.sh.in
bstreetest05j.sh: $(srcdir)/bstreetest05j.sh.in
bstreetest06l.sh: $(srcdir)/bstreetest06l.sh.in
bstreetest07n.sh: $(srcdir)/bstreetest07n.sh.in
bstreetest08p.sh: $(srcdir)/bstreetest08p.sh.in
bstreetest09r.sh: $(srcdir)/bstreetest09r.sh.in
bstreetest10t.sh: $(srcdir)/bstreetest10t.sh.in

check_SCRIPTS = bstreetest01b.sh bstreetest02d.sh bstreetest03f.sh \
	bstreetest04h.sh bstreetest05j.sh bstreetest06l.sh bstreetest07n.sh \
	bstreetest08p.sh bstreetest09r.sh bstreetest10t.sh


EXTRA_DIST = $(srcdir)/Test00StartingBSTree.txt.in \
	$(srcdir)/Test01Answer.txt.in $(srcdir)/Test02Answer.txt.in \
	$(srcdir)/Test03aAnswer.txt.in $(srcdir)/Test03bAnswer.txt.in \
	$(srcdir)/Test03ResultBSTree.txt.in $(srcdir)/Test04Answer.txt.in \
	$(srcdir)/Test05Answer.txt.in $(srcdir)/Test06Answer.txt.in \
	$(srcdir)/Test07aAnswer.txt.in $(srcdir)/Test07bAnswer.txt.in \
	$(srcdir)/Test07ResultBSTree.txt.in $(srcdir)/Test08Answer.txt.in \
	$(srcdir)/Test09Answer.txt.in $(srcdir)/Test10Answer.txt.in \
	$(srcdir)/bstreetest01b.sh.in $(srcdir)/bstreetest02d.sh.in \
	$(srcdir)/bstreetest03f.sh.in $(srcdir)/bstreetest04h.sh.in \
	$(srcdir)/bstreetest05j.sh.in $(srcdir)/bstreetest06l.sh.in \
	$(srcdir)/bstreetest07n.sh.in $(srcdir)/bstreetest08p.sh.in \
	$(srcdir)/bstreetest09r.sh.in $(srcdir)/bstreetest10t.sh.in


CLEANFILES = *.tmp *.sh *.txt

