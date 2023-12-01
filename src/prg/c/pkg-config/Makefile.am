#########################################################################
#									#
# Author: Copyright (C) 2015-2019, 2021-2023  Mark Grant		#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0-only					#
#									#
# Purpose:								#
#	AutoMake script file to generate libmgec pkgconfig from source.	#
#									#
#########################################################################


libmgec.pc: Makefile
	mkdir -p $(@D)
	rm -f $@
	$(edit) $(srcdir)/$(@F).in > $@

libmgec.pc: $(srcdir)/libmgec.pc.in

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libmgec.pc

EXTRA_DIST = $(srcdir)/libmgec.pc.in

CLEANFILES = libmgec.pc
