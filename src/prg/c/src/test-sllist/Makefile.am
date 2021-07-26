#########################################################################
#									#
# Script ID: src/prg/c/src/test-sllist/Makefile.am			#
# Author: Copyright (C) 2015-2019, 2021  Mark Grant			#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0					#
#									#
# Purpose:								#
#	AutoMake script file to generate sllist test program.		#
#	(The use of a libtool convenience library is OTT but done as an	#
#	exercise).							#
#									#
#########################################################################

#########################################################################
#									#
# Changelog								#
#									#
# Date		Author	Version	Description				#
#									#
# 02/05/2016	MG	1.0.1	First release.				#
# 13/01/2017	MG	1.0.2	Set debug or normal compile flags here.	#
# 25/03/2017	MG	1.0.3	Add temporary header directory.		#
# 27/10/2017	MG	1.0.4	Change to use _LDADD for temporary	#
#				libraries as passing -L and the temp	#
#				directory does not necessarily leave	#
#				LD_LIBRARY_PATH in the correct order.	#
#				Re-order into logical steps.		#
# 10/12/2017	MG	1.0.5	Add SPDX license tags to source files.	#
# 02/01/2018	MG	1.0.6	Move to new source directory structure.	#
# 09/01/2018	MG	1.0.7	Correct usage of config.h		#
# 04/07/2018	MG	1.0.8	Improve debug flags used. Use gdb	#
#				orientated level 3 (includes		#
#				pre-processor macros).			#
# 08/05/2019	MG	1.0.9	Remove shebang.				#
#				Merge into one project.			#
# 17/06/2019	MG	1.0.10	Move to check target.			#
# 05/07/2019	MG	1.0.11	Rewrite of the tests.			#
#				Add valgrind tests.			#
#				Add find next node test.		#
#				Add add_head test.			#
#				Add find_sll_node test.			#
# 25/07/2021	MG	1.0.12	Use CFLAGS prepared in configure.	#
#				Add conditional use Sparse CFLAGS.	#
# 26/07/2021	MG	1.0.13	Use CPPFLAGS prepared by configure.	#
#									#
#########################################################################


AM_CPPFLAGS = $(MG_CPPFLAGS)
AM_CPPFLAGS += -I$(srcdir)/../../inc-tmp -I$(srcdir)/../../inc
AM_CPPFLAGS += -I../../gen/inc -I../../gen/lib


AM_CFLAGS = $(MG_CFLAGS)
if DEBUG
AM_CFLAGS += -ggdb3 -Og
else
AM_CFLAGS += -O2
endif
if SPARSE
AM_CFLAGS += -Wsparse-all -Wno-vla
endif


check_HEADERS = sllisttest.h


check_LTLIBRARIES = libsllisttest.la
libsllisttest_la_SOURCES = common.c
libsllisttest_la_SOURCES += sllisttest01.c sllisttest02.c sllisttest03.c
libsllisttest_la_SOURCES += sllisttest04.c sllisttest05.c
libsllisttest_la_LIBADD = ../libmgec/libmgec.la $(tmplibraries)


check_PROGRAMS = sllisttest
sllisttest_SOURCES = main.c
sllisttest_LDADD = ./libsllisttest.la


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

