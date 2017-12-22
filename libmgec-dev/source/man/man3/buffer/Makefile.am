#! /usr/bin/env bash
#########################################################################
#									#
# Script ID: libmgec-dev/source/man/man3/buffer/Makefile.am		#
# Author: Copyright (C) 2015-2017  Mark Grant				#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0					#
#									#
# Purpose:								#
#	AutoMake script file to generate libmgec Section 3 buffer	#
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
#									#
#########################################################################


concat_buf.3 print_buf.3 trim_buf.3: Makefile
	mkdir -p $(@D)
	rm -f $@ $@.tmp
	$(edit) $(srcdir)/$(@F).man.in > $@.tmp
	txt2manwrap $(@F) 3 "MGE General C Library Manual" $@.tmp $@
	rm -f $@.tmp

concat_buf.3: $(srcdir)/concat_buf.3.man.in
print_buf.3: $(srcdir)/print_buf.3.man.in
trim_buf.3: $(srcdir)/trim_buf.3.man.in

man_MANS = concat_buf.3 print_buf.3 trim_buf.3

EXTRA_DIST = $(srcdir)/concat_buf.3.man.in $(srcdir)/print_buf.3.man.in \
		$(srcdir)/trim_buf.3.man.in

CLEANFILES = *.tmp concat_buf.3 print_buf.3 trim_buf.3
