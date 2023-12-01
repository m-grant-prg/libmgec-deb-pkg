#########################################################################
#									#
# Author: Copyright (C) 2015-2019, 2021, 2023  Mark Grant		#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0-only					#
#									#
# Purpose:								#
#	AutoMake script file to generate libmgec Section 3 errno	#
# manual pages from source.						#
#									#
#########################################################################


mge_strerror.3: Makefile
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

mge_strerror.3: $(srcdir)/mge_strerror.3.man.in

man_MANS = mge_strerror.3

EXTRA_DIST = $(srcdir)/mge_strerror.3.man.in

CLEANFILES = *.tmp mge_strerror.3

