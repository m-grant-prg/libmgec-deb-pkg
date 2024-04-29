#########################################################################
#									#
# Author: Copyright (C) 2015-2019, 2021-2023  Mark Grant		#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0-only					#
#									#
# Purpose:								#
#	AutoMake script file to generate libmgec library from source.	#
#									#
#########################################################################


if DEBUG
AM_CPPFLAGS = $(MG_DEBUG_CPPFLAGS)
else
AM_CPPFLAGS = $(MG_CPPFLAGS)
endif
AM_CPPFLAGS += -I$(srcdir)/../../inc-tmp -I$(srcdir)/../../inc
AM_CPPFLAGS += -I../../gen/inc -I../../gen/lib
libmgec_la_CPPFLAGS = $(DEF_CPP_VALUES) $(AM_CPPFLAGS)


# If after an initial build another build either overrides default values from
# the make / bootstrap CL, or, ceases to do so, or uses different values, then
# make, which works on timestamps of files, will see no change and so it will
# not -re-compile. Re-compiling is a must, so touch the source file(s) which
# define the values to force a re-compile.
.PHONY: all-local
all-local:
	touch $(srcdir)/buf-msg/internal.h


if DEBUG
AM_CFLAGS = $(MG_DEBUG_CFLAGS)
else
AM_CFLAGS = $(MG_CFLAGS)
endif
if HEADERCHECK
AM_CFLAGS += -H
endif
if SPARSE
AM_CFLAGS += -Wsparse-all -Wno-vla
endif
if ANALYZER
AM_CFLAGS += $(MG_ANALYZER_CFLAGS)
endif


noinst_HEADERS = buf-msg/internal.h errors/internal.h
noinst_HEADERS += listsandsorts/internal.h


lib_LTLIBRARIES = libmgec.la


libmgec_la_SOURCES = buf-msg/buffer.c buf-msg/message.c
libmgec_la_SOURCES += errors/errno.c errors/error.c
libmgec_la_SOURCES += listsandsorts/bstree.c listsandsorts/dllist.c
libmgec_la_SOURCES += listsandsorts/sllist.c
libmgec_la_SOURCES += memory/memory.c
libmgec_la_SOURCES += version.c


AM_LDFLAGS = $(MG_LDFLAGS)
AM_LDFLAGS += -version-info @lib_version_info@


libmgec_la_LIBADD = $(tmplibraries)

