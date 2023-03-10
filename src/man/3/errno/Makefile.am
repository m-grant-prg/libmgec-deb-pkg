#########################################################################
#									#
# Script ID: src/man/3/errno/Makefile.am				#
# Author: Copyright (C) 2015-2019, 2021  Mark Grant			#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0-only					#
#									#
# Purpose:								#
#	AutoMake script file to generate libmgec Section 3 errno	#
# manual pages from source.						#
#									#
#########################################################################

#########################################################################
#									#
# Changelog								#
#									#
# Date		Author	Version	Description				#
#									#
# 24/01/2017	MG	1.0.1	First release.				#
# 23/04/2017	MG	1.0.2	Correct ignoring of $(edit) result.	#
#				Change source extensions to .man.in	#
# 22/12/2017	MG	1.0.3	Add SPDX license tags to source files.	#
# 31/12/2017	MG	1.0.4	Determine the manual section from the	#
#				target suffix. If the suffix is blank	#
#				(foo.) or if there is no suffix (foo)	#
#				then error out.				#
# 02/01/2018	MG	1.0.5	Move to new source directory structure.	#
# 10/05/2019	MG	1.0.6	Remove shebang.				#
#				Merge into one project.			#
# 03/12/2021	MG	1.0.7	Tighten SPDX tag.			#
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

