#########################################################################
#									#
# Script ID: src/prg/c/src/test-dllist/Makefile.am			#
# Author: Copyright (C) 2015-2019, 2021, 2022  Mark Grant		#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0-only					#
#									#
# Purpose:								#
#	AutoMake script file to generate dllist test program.		#
#									#
#########################################################################

#########################################################################
#									#
# Changelog								#
#									#
# Date		Author	Version	Description				#
#									#
# 06/05/2016	MG	1.0.1	First release.				#
# 13/01/2017	MG	1.0.2	Set debug or normal compile flags here.	#
# 25/03/2017	MG	1.0.3	Add temporary header directory.		#
# 127/10/2017	MG	1.0.4	Change to use _LDADD for temporary	#
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
# 10/05/2019	MG	1.0.9	Remove shebang.				#
#				Merge into one project.			#
# 17/06/2019	MG	1.0.10	Move under check target.		#
# 25/07/2021	MG	1.0.11	Use CFLAGS prepared in configure.	#
#				Add conditional use Sparse CFLAGS.	#
# 26/07/2021	MG	1.0.12	Use CPPFLAGS prepared by configure.	#
#				Use LDFLAGS prepared by configure.	#
# 15/10/2021	MG	1.0.13	Change debug optimisation to -O0	#
# 05/11/2021	MG	1.0.14	Use (non-)debug CPPFLAGS from configure	#
#				Use (non-)debug CFLAGS from configure	#
# 03/12/2021	MG	1.0.15	Tighten SPDX tag.			#
# 30/09/2022	MG	1.0.16	Re-order tmplibraries.			#
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


check_PROGRAMS = dllisttest
dllisttest_SOURCES = main.c


AM_LDFLAGS = $(MG_LDFLAGS)


LDADD = $(tmplibraries)
LDADD += ../libmgec/libmgec.la

