#! /usr/bin/env bash
#########################################################################
#									#
# Script ID: libmgec-doc/docs/doxygen/Makefile.am			#
# Author: Copyright (C) 2017  Mark Grant				#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0					#
#									#
# Purpose:								#
#	AutoMake script file to produce doxygen html documentation.	#
#									#
#########################################################################

#########################################################################
#									#
# Changelog								#
#									#
# Date		Author	Version	Description				#
#									#
# 21/12/2017	MG	1.0.0	First release.				#
#									#
#########################################################################


docpkg = $(PACKAGE_TARNAME)-doxy-$(PACKAGE_VERSION).tar.gz


$(docpkg): doxygen.stamp
	tar chof - html | gzip -9 -c >$@

doxygen.stamp: Doxyfile
	doxygen $<
	echo Timestamp > $@


html_DATA = $(docpkg)


install-data-hook:
	cd $(DESTDIR)$(htmldir) && tar xf $(docpkg)

uninstall-hook:
	cd $(DESTDIR)$(htmldir) && rm -rf html


CLEANFILES = doxywarn.txt doxygen.stamp $(docpkg)

clean-local:
	rm -rf html
