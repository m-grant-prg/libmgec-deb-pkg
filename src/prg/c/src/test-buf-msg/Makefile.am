#########################################################################
#									#
# Script ID: src/prg/c/src/test-buf-msg/Makefile.am			#
# Author: Copyright (C) 2018-2019, 2021, 2022  Mark Grant		#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0-only					#
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
# 26/07/2021	MG	1.0.5	Use CPPFLAGS prepared by configure.	#
#				Use LDFLAGS prepared by configure.	#
# 15/10/2021	MG	1.0.6	Change debug optimisation to -O0	#
# 05/11/2021	MG	1.0.7	Use (non-)debug CPPFLAGS from configure	#
#				Use (non-)debug CFLAGS from configure	#
# 03/12/2021	MG	1.0.8	Tighten SPDX tag.			#
# 16/09/2022	MG	1.0.9	Rename tmplibraries.			#
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


check_PROGRAMS = bufmsgtest
bufmsgtest_SOURCES = main.c


AM_LDFLAGS = $(MG_LDFLAGS)


LDADD = ../libmgec/libmgec.la
LDADD += $(tmplibraries_depth_2)

