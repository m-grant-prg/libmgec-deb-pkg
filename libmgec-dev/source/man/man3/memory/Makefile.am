#! /usr/bin/env bash
#########################################################################
#									#
# Script ID: libmgec-dev/source/man/man3/memory/Makefile.am		#
# Author: Copyright (C) 2015-2017  Mark Grant				#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0					#
#									#
# Purpose:								#
#	AutoMake script file to generate libmgec Section 3 memory	#
# manual pages from source.						#
#									#
#########################################################################

#########################################################################
#									#
# Changelog								#
#									#
# Date		Author	Version	Description				#
#									#
# 30/12/2016	MG	1.0.1	First release.				#
# 23/04/2017	MG	1.0.2	Correct ignoring of $(edit) result.	#
#				Change source extensions to .man.in	#
# 22/12/2017	MG	1.0.3	Add SPDX license tags to source files.	#
#									#
#########################################################################


mg_realloc.3: Makefile
	mkdir -p $(@D)
	rm -f $@ $@.tmp
	$(edit) $(srcdir)/$(@F).man.in > $@.tmp
	txt2manwrap $(@F) 3 "MGE General C Library Manual" $@.tmp $@
	rm -f $@.tmp

mg_realloc.3: $(srcdir)/mg_realloc.3.man.in

man_MANS = mg_realloc.3

EXTRA_DIST = $(srcdir)/mg_realloc.3.man.in

CLEANFILES = *.tmp mg_realloc.3
