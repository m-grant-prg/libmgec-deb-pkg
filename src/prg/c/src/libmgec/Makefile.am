#########################################################################
#									#
# Script ID: src/prg/c/src/libmgec/Makefile.am				#
# Author: Copyright (C) 2015-2019, 2021, 2022  Mark Grant		#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0-only					#
#									#
# Purpose:								#
#	AutoMake script file to generate libmgec library from source.	#
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
# 07/11/2015	MG	1.0.4	Include base.c build.			#
# 02/05/2016	MG	1.0.5	Add Singly Linked List functionality.	#
# 06/05/2016	MG	1.0.6	Add Doubly Linked List functionality.	#
# 15/11/2016	MG	1.0.7	Add buffer, message and memory sources.	#
# 13/01/2017	MG	1.0.8	Set debug or normal compile flags here.	#
# 24/01/2017	MG	1.0.9	Change for new source directory		#
#				structure and new error sources.	#
#				Remove un-needed base.c.		#
# 25/03/2017	MG	1.0.10	Add temporary header directory.		#
# 09/06/2017	MG	1.0.11	Add support for temporary libraries.	#
# 27/10/2017	MG	1.0.12	Change to use _LIBADD for temporary	#
#				libraries as passing -L and the temp	#
#				directory does not necessarily leave	#
#				LD_LIBRARY_PATH in the correct order.	#
#				Re-order into logical steps.		#
# 10/12/2017	MG	1.0.13	Add SPDX license tags to source files.	#
# 02/01/2018	MG	1.0.14	Move to new source directory structure.	#
# 09/01/2018	MG	1.0.15	Correct usage of config.h		#
# 26/03/2018	MG	1.0.16	Add support for sparse.			#
# 19/05/2018	MG	1.0.17	Add new errors/internal.h		#
# 19/06/2018	MG	1.0.18	Disable sparse variable length array	#
#				warnings.				#
# 20/06/2018	MG	1.0.19	Use lib_version_info AC_SUBST variable	#
#				passed via AC_CONFIG_FILES to enable	#
#				all top level versioning to be done in	#
#				configure.ac				#
# 04/07/2018	MG	1.0.20	Improve debug flags used. Use gdb	#
#				orientated level 3 (includes		#
#				pre-processor macros).			#
# 08/08/2018	MG	1.0.21	Support configure time otion to add -H	#
#				compiler flag to show included files	#
#				and their depth in the include stack.	#
#				Use compiler version dependent CFLAGS	#
#				assembled in configure.			#
# 09/09/2018	MG	1.0.22	Add buf-msg/internal.h			#
# 10/05/2019	MG	1.0.23	Remove shebang.				#
#				Merge into one project.			#
# 12/07/2019	MG	1.0.24	Change for individual internal header	#
#				files in listsandsorts.			#
# 15/04/2021	MG	1.0.25	Add target CPPFLAGS to amend some	#
#				default values passed on the configure	#
#				CL.					#
# 26/07/2021	MG	1.0.26	Use CPPFLAGS prepared by configure.	#
#				Use LDFLAGS prepared by configure.	#
# 15/10/2021	MG	1.0.27	Change debug optimisation to -O0	#
# 05/11/2021	MG	1.0.28	Use (non-)debug CPPFLAGS from configure	#
#				Use (non-)debug CFLAGS from configure	#
# 03/12/2021	MG	1.0.29	Tighten SPDX tag.			#
# 10/06/2022	MG	1.0.30	Add compiler analyzer option.		#
# 03/09/2022	MG	1.0.31	Remove now deleted dllist-internal.	#
#				Remove now deleted sllist-internal.	#
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
noinst_HEADERS += listsandsorts/bstree-internal.h


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

