#########################################################################
#									#
# Script ID: src/prg/c/src/test-buf-msg/Makefile.am			#
# Author: Copyright (C) 2018-2019, 2021  Mark Grant			#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0					#
#									#
# Purpose:								#
#	AutoMake script file to generate buffers and messages test	#
#	program.							#
#									#
#########################################################################

#########################################################################
#									#
# Changelog								#
#									#
# Date		Author	Version	Description				#
#									#
# 06/09/2018	MG	1.0.1	First release.				#
# 10/05/2019	MG	1.0.2	Remove shebang.				#
#				Merge into one project.			#
# 17/06/2019	MG	1.0.3	Move under check target.		#
# 25/07/2021	MG	1.0.4	Use CFLAGS prepared in configure.	#
#				Add conditional use Sparse CFLAGS.	#
#									#
#########################################################################


AM_CPPFLAGS = -I$(srcdir)/../../inc-tmp -I$(srcdir)/../../inc
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


check_PROGRAMS = bufmsgtest
bufmsgtest_SOURCES = main.c


LDADD = ../libmgec/libmgec.la
LDADD += $(tmplibraries)

