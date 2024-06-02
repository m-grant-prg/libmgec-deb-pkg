#########################################################################
#									#
# Author: Copyright (C) 2018-2019, 2021-2024  Mark Grant		#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0-only					#
#									#
# Purpose:								#
#	AutoMake script file to generate buffers and messages test	#
#	program.							#
#									#
#########################################################################


if DEBUG
.gdbinit: Makefile
	mkdir -p $(@D)
	rm -f $@ $@.tmp
	no_dot_target=`echo $@ | sed "s/^.//"`; \
		test -f ./$${no_dot_target}.in || srcdir=$(srcdir)/; \
		no_dot_file=`echo $(@F) | sed "s/^.//"`; \
		$(edit) $${srcdir}$${no_dot_file}.in > $@.tmp
	mv $@.tmp $@
.gdbinit: $(srcdir)/gdbinit.in

check_SCRIPTS = .gdbinit
endif


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


check_PROGRAMS = bufmsgtest
bufmsgtest_SOURCES = main.c


AM_LDFLAGS = $(MG_LDFLAGS)


LDADD = $(tmplibraries)
LDADD += ../libmgec/libmgec.la


EXTRA_DIST = $(srcdir)/gdbinit.in


CLEANFILES = *.tmp .gdbinit

