#########################################################################
#									#
# Author: Copyright (C) 2015-2019, 2021-2023  Mark Grant		#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0-only					#
#									#
# Purpose:								#
#	AutoMake script file to generate sllist test program.		#
#	(The use of a libtool convenience library is OTT but done as an	#
#	exercise).							#
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


AM_LDFLAGS = $(MG_LDFLAGS)


check_HEADERS = sllisttest.h


check_LTLIBRARIES = libsllisttest.la
libsllisttest_la_SOURCES = common.c
libsllisttest_la_SOURCES += sllisttest01.c sllisttest02.c sllisttest03.c
libsllisttest_la_SOURCES += sllisttest04.c sllisttest05.c


check_PROGRAMS = sllisttest
sllisttest_SOURCES = main.c


LDADD = $(tmplibraries)
LDADD += ../libmgec/libmgec.la
LDADD += ./libsllisttest.la


Test01Answer.txt Test02Answer.txt Test03Answer.txt Test04Answer.txt \
	Test05Answer.txt: Makefile
	mkdir -p $(@D)
	rm -f $@ $@.tmp
	test -f ./$@.in || srcdir=$(srcdir)/; \
	cp $${srcdir}$(@F).in  $@
Test01Answer.txt: $(srcdir)/Test01Answer.txt.in
Test02Answer.txt: $(srcdir)/Test02Answer.txt.in
Test03Answer.txt: $(srcdir)/Test03Answer.txt.in
Test04Answer.txt: $(srcdir)/Test04Answer.txt.in
Test05Answer.txt: $(srcdir)/Test05Answer.txt.in

check_DATA = Test01Answer.txt Test02Answer.txt Test03Answer.txt \
	Test04Answer.txt Test05Answer.txt


sllisttest01.sh sllisttest01vg.sh sllisttest02.sh sllisttest02vg.sh \
	sllisttest03.sh sllisttest03vg.sh \
	sllisttest04.sh sllisttest04vg.sh \
	sllisttest05.sh sllisttest05vg.sh: Makefile
	mkdir -p $(@D)
	rm -f $@ $@.tmp
	test -f ./$@.in || srcdir=$(srcdir)/; \
	$(edit) $${srcdir}$(@F).in > $@.tmp
	mv $@.tmp $@
	chmod a+x $@
sllisttest01.sh: $(srcdir)/sllisttest01.sh.in
sllisttest01vg.sh: $(srcdir)/sllisttest01vg.sh.in
sllisttest02.sh: $(srcdir)/sllisttest02.sh.in
sllisttest02vg.sh: $(srcdir)/sllisttest02vg.sh.in
sllisttest03.sh: $(srcdir)/sllisttest03.sh.in
sllisttest03vg.sh: $(srcdir)/sllisttest03vg.sh.in
sllisttest04.sh: $(srcdir)/sllisttest04.sh.in
sllisttest04vg.sh: $(srcdir)/sllisttest04vg.sh.in
sllisttest05vg.sh: $(srcdir)/sllisttest05vg.sh.in

check_SCRIPTS = sllisttest01.sh sllisttest01vg.sh \
		sllisttest02.sh sllisttest02vg.sh \
		sllisttest03.sh sllisttest03vg.sh \
		sllisttest04.sh sllisttest04vg.sh \
		sllisttest05.sh sllisttest05vg.sh

EXTRA_DIST = $(srcdir)/Test01Answer.txt.in $(srcdir)/Test02Answer.txt.in \
	$(srcdir)/Test03Answer.txt.in $(srcdir)/Test04Answer.txt.in \
	$(srcdir)/Test05Answer.txt.in \
	$(srcdir)/sllisttest01.sh.in $(srcdir)/sllisttest01vg.sh.in \
	$(srcdir)/sllisttest02.sh.in $(srcdir)/sllisttest02vg.sh.in \
	$(srcdir)/sllisttest03.sh.in $(srcdir)/sllisttest03vg.sh.in \
	$(srcdir)/sllisttest04.sh.in $(srcdir)/sllisttest04vg.sh.in \
	$(srcdir)/sllisttest05.sh.in $(srcdir)/sllisttest05vg.sh.in


CLEANFILES = *.tmp *.sh *.txt

