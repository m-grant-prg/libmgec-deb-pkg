#! /usr/bin/env bash
#########################################################################
#									#
# Script ID: dev/source/man/man3/message/Makefile.am			#
# Author: Copyright (C) 2015-2018  Mark Grant				#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0					#
#									#
# Purpose:								#
#	AutoMake script file to generate libmgec Section 3 message	#
# manual pages from source.						#
#									#
#########################################################################

#########################################################################
#									#
# Changelog								#
#									#
# Date		Author	Version	Description				#
#									#
# 31/12/2016	MG	1.0.1	First release.				#
# 23/04/2017	MG	1.0.2	Correct ignoring of $(edit) result.	#
#				Change source extensions to .man.in	#
# 22/12/2017	MG	1.0.3	Add SPDX license tags to source files.	#
# 31/12/2017	MG	1.0.4	Determine the manual section from the	#
#				target suffix. If the suffix is blank	#
#				(foo.) or if there is no suffix (foo)	#
#				then error out.				#
# 02/01/2018	MG	1.0.5	Move to new source directory structure.	#
#									#
#########################################################################


clear_msg.3 deconstruct_msg.3 get_msg.3 print_msg.3 pull_msg.3: Makefile
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

clear_msg.3: $(srcdir)/clear_msg.3.man.in
deconstruct_msg.3: $(srcdir)/deconstruct_msg.3.man.in
get_msg.3: $(srcdir)/get_msg.3.man.in
print_msg.3: $(srcdir)/print_msg.3.man.in
pull_msg.3: $(srcdir)/pull_msg.3.man.in
man_MANS = clear_msg.3 deconstruct_msg.3 get_msg.3 print_msg.3 pull_msg.3

EXTRA_DIST = $(srcdir)/clear_msg.3.man.in $(srcdir)/deconstruct_msg.3.man.in \
		$(srcdir)/get_msg.3.man.in $(srcdir)/print_msg.3.man.in \
		$(srcdir)/pull_msg.3.man.in

CLEANFILES = *.tmp clear_msg.3 deconstruct_msg.3 get_msg.3 print_msg.3 \
		pull_msg.3
