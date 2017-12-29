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
# 28/12/2017	MG	1.0.0	First release.				#
#									#
#########################################################################


docpkg = $(PACKAGE_TARNAME)-doxy-$(PACKAGE_VERSION).tar.gz


# The dependencies below start with Doxyfile which is produced by configure, so
# thereafter no updates to these documents will happen by make alone. Re-run
# configure and make, or, delete the stamp file and run make to force an update.
#
# The test for the -lib and -dev sources ensures that the Doxygen documentation
# and resulting tarball are updated only when the sources are present. The
# importance of this is that during make install for this -doc package the
# sources are not present and make all would would produce basic empty Doxygen
# documentation which would then be installed.

$(docpkg): doxygen.stamp
	if [ -d $(top_srcdir)/../libmgec-lib/source/ \
		-a -d $(top_srcdir)/../libmgec-dev/source/ ]; \
		then tar chof - html | gzip -9 -c > $@; fi

doxygen.stamp: Doxyfile
	if [ -d $(top_srcdir)/../libmgec-lib/source/ \
		-a -d $(top_srcdir)/../libmgec-dev/source/ ]; \
		then doxygen $<; fi
	echo Timestamp > $@


html_DATA = $(docpkg)


install-data-hook:
	cd $(DESTDIR)$(htmldir) && tar xf $(docpkg)

uninstall-hook:
	cd $(DESTDIR)$(htmldir) && rm -rf html


EXTRA_DIST = $(docpkg)


CLEANFILES = doxywarn.txt doxygen.stamp $(docpkg)

clean-local:
	rm -rf html
