#########################################################################
#									#
# Author: Copyright (C) 2015-2021, 2023  Mark Grant			#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0-only					#
#									#
# Purpose:								#
#	AutoMake script file to generate libmgec Section 3 bstree	#
# manual pages from source.						#
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

