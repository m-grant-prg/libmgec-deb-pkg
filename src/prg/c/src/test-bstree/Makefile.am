#########################################################################
#									#
# Author: Copyright (C) 2015-2019, 2021-2023  Mark Grant		#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0-only					#
#									#
# Purpose:								#
#	AutoMake script file to generate bstree test program.		#
#									#
#########################################################################


if DEBUG
AM_CPPFLAGS = $(MG_DEBUG_CPPFLAGS)
else
AM_CPPFLAGS = $(MG_CPPFLAGS)
endif
AM_CPPFLAGS += -I$(srcdir)/../../inc-tmp -I$(srcdir)/../../inc
AM_CPPFLAGS += -I../../gen/inc -I../../gen/lib


if DEBUG
AM_CFLAGS = $(MG_DEBUG_CFLAGS)
else
AM_CFLAGS = $(MG_CFLAGS)
endif
if SPARSE
AM_CFLAGS += -Wsparse-all -Wno-vla
endif


check_PROGRAMS = bstreetest
bstreetest_SOURCES = main.c


AM_LDFLAGS = $(MG_LDFLAGS)


LDADD = $(tmplibraries)
LDADD += ../libmgec/libmgec.la


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

