#! /usr/bin/env bash
#########################################################################
#									#
# Script ID: dev/src/man/3/bstree/Makefile.am				#
# Author: Copyright (C) 2015-2018  Mark Grant				#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0					#
#									#
# Purpose:								#
#	AutoMake script file to generate libmgec Section 3 bstree	#
# manual pages from source.						#
#									#
#########################################################################

#########################################################################
#									#
# Changelog								#
#									#
# Date		Author	Version	Description				#
#									#
# 26/08/2015	MG	1.0.1	Started versioning of this script.	#
# 17/09/2015	MG	1.0.2	Change to use cnv2man script which	#
#				eliminates problems caused by the .3	#
#				extensions.				#
# 20/09/2015	MG	1.0.3	Convert to use txt2manwrap.		#
# 25/10/2015	MG	1.0.4	Restructure and change to conform to	#
#				AutoTools General Template v1.0.6.	#
# 03/11/2015	MG	1.0.5	Change from bt and btree names to bst	#
#				and bstree as this is a binary search	#
#				tree, not a b-tree.			#
# 13/04/2017	MG	1.0.6	Overhaul for new bstree object.		#
#				Change source file suffixes to .man.in	#
# 22/12/2017	MG	1.0.7	Add SPDX license tags to source files.	#
# 31/12/2017	MG	1.0.8	Determine the manual section from the	#
#				target suffix. If the suffix is blank	#
#				(foo.) or if there is no suffix (foo)	#
#				then error out.				#
# 02/01/2018	MG	1.0.9	Move to new source directory structure.	#
#									#
#########################################################################


add_bst_node.3 cre_bst.3 del_bst.3 del_bst_node.3 find_bst_node.3 \
	find_next_bst_node.3 find_next_bst_node_trace.3 find_prev_bst_node.3 \
	get_counter_bst_node.3 upd_bst_node.3: Makefile
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

add_bst_node.3: $(srcdir)/add_bst_node.3.man.in
cre_bst.3: $(srcdir)/cre_bst.3.man.in
del_bst.3: $(srcdir)/del_bst.3.man.in
del_bst_node.3: $(srcdir)/del_bst_node.3.man.in
find_bst_node.3: $(srcdir)/find_bst_node.3.man.in
find_next_bst_node.3: $(srcdir)/find_next_bst_node.3.man.in
find_next_bst_node_trace.3: $(srcdir)/find_next_bst_node_trace.3.man.in
find_prev_bst_node.3: $(srcdir)/find_prev_bst_node.3.man.in
get_counter_bst_node.3: $(srcdir)/get_counter_bst_node.3.man.in
upd_bst_node.3: $(srcdir)/upd_bst_node.3.man.in

man_MANS = add_bst_node.3 cre_bst.3 del_bst.3 del_bst_node.3 find_bst_node.3 \
	find_next_bst_node.3 find_next_bst_node_trace.3 find_prev_bst_node.3 \
	get_counter_bst_node.3 upd_bst_node.3

EXTRA_DIST = $(srcdir)/add_bst_node.3.man.in $(srcdir)/cre_bst.3.man.in \
	$(srcdir)/del_bst.3.man.in $(srcdir)/del_bst_node.3.man.in \
	$(srcdir)/find_bst_node.3.man.in $(srcdir)/find_next_bst_node.3.man.in \
	$(srcdir)/find_next_bst_node_trace.3.man.in \
	$(srcdir)/find_prev_bst_node.3.man.in \
	$(srcdir)/get_counter_bst_node.3.man.in $(srcdir)/upd_bst_node.3.man.in

CLEANFILES = *.tmp add_bst_node.3 cre_bst.3 del_bst.3 del_bst_node.3 \
	find_bst_node.3 find_next_bst_node.3 find_next_bst_node_trace.3 \
	find_prev_bst_node.3 get_counter_bst_node.3 upd_bst_node.3
