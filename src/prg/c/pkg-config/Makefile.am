#########################################################################
#									#
# Script ID: src/prg/c/pkg-config/Makefile.am				#
# Author: Copyright (C) 2015-2019, 2021, 2022  Mark Grant		#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0-only					#
#									#
# Purpose:								#
#	AutoMake script file to generate libmgec pkgconfig from source.	#
#									#
#########################################################################

#########################################################################
#									#
# Changelog								#
#									#
# Date		Author	Version	Description				#
#									#
# 12/07/2015	MG	1.0.1	First release.				#
# 25/10/2015	MG	1.0.2	Restructure and change to conform to	#
#				AutoTools General Template v1.0.6.	#
# 22/12/2017	MG	1.0.3	Add SPDX license tags to source files.	#
# 02/01/2018	MG	1.0.4	Move to new source directory structure.	#
# 06/05/2019	MG	1.0.5	Remove shebang.				#
# 03/12/2021	MG	1.0.6	Tighten SPDX tag.			#
# 20/08/2022	MG	1.0.7	Perform variable substitution here	#
#				rather than with AC_CONFIG_FILES.	#
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
