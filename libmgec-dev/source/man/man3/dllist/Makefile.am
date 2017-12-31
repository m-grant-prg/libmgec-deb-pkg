#! /usr/bin/env bash
#########################################################################
#									#
# Script ID: libmgec-dev/source/man/man3/dllist/Makefile.am		#
# Author: Copyright (C) 2015-2017  Mark Grant				#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0					#
#									#
# Purpose:								#
#	AutoMake script file to generate libmgec Section 3 dllist	#
# manual pages from source.						#
#									#
#########################################################################

#########################################################################
#									#
# Changelog								#
#									#
# Date		Author	Version	Description				#
#									#
# 06/05/2016	MG	1.0.1	First release.				#
# 23/04/2017	MG	1.0.2	Correct ignoring of $(edit) result.	#
#				Change source extensions to .man.in	#
# 22/12/2017	MG	1.0.3	Add SPDX license tags to source files.	#
# 31/12/2017	MG	1.0.4	Determine the manual section from the	#
#				target suffix. If the suffix is blank	#
#				(foo.) or if there is no suffix (foo)	#
#				then error out.				#
#									#
#########################################################################


add_dll_node.3 find_prev_dll_node.3 find_next_dll_node.3 free_dllist.3: Makefile
	mkdir -p $(@D)
	rm -f $@ $@.tmp
	$(edit) $(srcdir)/$(@F).man.in > $@.tmp
	targfile=$(@F);	\
	if [[ $$targfile == *"."* ]]; then \
		if [[ $${targfile##*.} == "" ]]; then \
			echo "Source file suffix used as section but empty."; \
			exit 1; \
		else \
			section=$${targfile##*.}; \
		fi; \
	else \
		echo "Source file suffix used as section but no dot & empty."; \
		exit 1; \
	fi; \
	txt2manwrap $(@F) $$section "MGE General C Library Manual" $@.tmp $@
	rm -f $@.tmp

add_dll_node.3: $(srcdir)/add_dll_node.3.man.in
find_prev_dll_node.3: $(srcdir)/find_prev_dll_node.3.man.in
find_next_dll_node.3: $(srcdir)/find_next_dll_node.3.man.in
free_dllist.3: $(srcdir)/free_dllist.3.man.in

man_MANS = add_dll_node.3 find_prev_dll_node.3 find_next_dll_node.3 \
	free_dllist.3

EXTRA_DIST = $(srcdir)/add_dll_node.3.man.in \
	$(srcdir)/find_prev_dll_node.3.man.in \
	$(srcdir)/find_next_dll_node.3.man.in $(srcdir)/free_dllist.3.man.in

CLEANFILES = *.tmp add_dll_node.3 find_prev_dll_node.3 find_next_dll_node.3 \
	free_dllist.3
