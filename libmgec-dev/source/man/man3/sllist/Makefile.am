#! /usr/bin/env bash
#########################################################################
#									#
# Script ID: libmgec-dev/source/man/man3/sllist/Makefile.am		#
# Author: Copyright (C) 2015-2017  Mark Grant				#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0					#
#									#
# Purpose:								#
#	AutoMake script file to generate libmgec Section 3 sllist	#
# manual pages from source.						#
#									#
#########################################################################

#########################################################################
#									#
# Changelog								#
#									#
# Date		Author	Version	Description				#
#									#
# 03/05/2016	MG	1.0.1	First release.				#
# 23/04/2017	MG	1.0.2	Correct ignoring of $(edit) result.	#
#				Change source extensions to .man.in	#
# 22/12/2017	MG	1.0.3	Add SPDX license tags to source files.	#
#									#
#########################################################################


add_sll_node.3 find_next_sll_node.3 free_sllist.3: Makefile
	mkdir -p $(@D)
	rm -f $@ $@.tmp
	$(edit) $(srcdir)/$(@F).man.in > $@.tmp
	txt2manwrap $(@F) 3 "MGE General C Library Manual" $@.tmp $@
	rm -f $@.tmp

add_sll_node.3: $(srcdir)/add_sll_node.3.man.in
find_next_sll_node.3: $(srcdir)/find_next_sll_node.3.man.in
free_sllist.3: $(srcdir)/free_sllist.3.man.in

man_MANS = add_sll_node.3 find_next_sll_node.3 free_sllist.3

EXTRA_DIST = $(srcdir)/add_sll_node.3.man.in \
	$(srcdir)/find_next_sll_node.3.man.in $(srcdir)/free_sllist.3.man.in

CLEANFILES = *.tmp add_sll_node.3 find_next_sll_node.3 free_sllist.3
