#########################################################################
#									#
# Author: Copyright (C) 2015-2021, 2023  Mark Grant			#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0-only					#
#									#
# Purpose:								#
#	AutoMake script file to generate libmgec Section 3 sllist	#
# manual pages from source.						#
#									#
#########################################################################


add_head_sll_node.3 add_tail_sll_node.3 find_next_sll_node.3 find_sll_node.3 \
	for_each_sll_node.3 free_sllist.3: Makefile
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

add_head_sll_node.3: $(srcdir)/add_head_sll_node.3.man.in
add_tail_sll_node.3: $(srcdir)/add_tail_sll_node.3.man.in
find_next_sll_node.3: $(srcdir)/find_next_sll_node.3.man.in
find_sll_node.3: $(srcdir)/find_sll_node.3.man.in
for_each_sll_node.3: $(srcdir)/for_each_sll_node.3.man.in
free_sllist.3: $(srcdir)/free_sllist.3.man.in

man_MANS = add_head_sll_node.3 add_tail_sll_node.3 find_next_sll_node.3 \
	find_sll_node.3 for_each_sll_node.3 free_sllist.3

EXTRA_DIST = $(srcdir)/add_head_sll_node.3.man.in \
	$(srcdir)/add_tail_sll_node.3.man.in \
	$(srcdir)/find_next_sll_node.3.man.in $(srcdir)/find_sll_node.3.man.in \
	$(srcdir)/for_each_sll_node.3.man.in $(srcdir)/free_sllist.3.man.in

CLEANFILES = *.tmp add_head_sll_node.3 add_tail_sll_node.3 \
	find_next_sll_node.3 find_sll_node.3 for_each_sll_node.3 free_sllist.3

