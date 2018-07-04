#! /usr/bin/env bash
#########################################################################
#									#
# Script ID: lib/src/prg/c/src/test-errno/Makefile.am			#
# Author: Copyright (C) 2015-2018  Mark Grant				#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0					#
#									#
# Purpose:								#
#	AutoMake script file to generate errno test program.		#
#									#
#########################################################################

#########################################################################
#									#
# Changelog								#
#									#
# Date		Author	Version	Description				#
#									#
# 22/01/2017	MG	1.0.1	First release.				#
# 25/03/2017	MG	1.0.2	Add temporary header directory.		#
# 27/10/2017	MG	1.0.3	Change to use _LDADD for temporary	#
#				libraries as passing -L and the temp	#
#				directory does not necessarily leave	#
#				LD_LIBRARY_PATH in the correct order.	#
#				Re-order into logical steps.		#
# 10/12/2017	MG	1.0.4	Add SPDX license tags to source files.	#
# 02/01/2018	MG	1.0.5	Move to new source directory structure.	#
# 09/01/2018	MG	1.0.6	Correct usage of config.h		#
# 04/07/2018	MG	1.0.7	Improve debug flags used. Use gdb	#
#				orientated level 3 (includes		#
#				pre-processor macros).			#
#									#
#########################################################################


AM_CPPFLAGS = -I$(srcdir)/../../inc-tmp -I$(srcdir)/../../inc
AM_CPPFLAGS += -I$(top_srcdir)/../dev/src/prg/c/inc
AM_CPPFLAGS += -I../../gen/inc -I../../gen/lib


AM_CFLAGS = -Wall

if DEBUG
AM_CFLAGS += -ggdb3 -Og
else
AM_CFLAGS += -O2
endif


noinst_PROGRAMS = errnotest
errnotest_SOURCES = main.c


LDADD = ../libmgec/libmgec.la
LDADD += $(tmplibraries)
