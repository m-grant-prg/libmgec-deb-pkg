#########################################################################
#									#
# Script ID: doc/doxygen/Makefile.am					#
# Author: Copyright (C) 2017-2019  Mark Grant				#
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
# 28/12/2017	MG	1.0.1	First release.				#
# 02/01/2018	MG	1.0.2	Move to new source directory structure.	#
# 17/01/2018	MG	1.0.3	Update checks for source after source	#
#				directory change.			#
# 11/02/2018	MG	1.0.4	Make tar use the Posix format for	#
#				longer filenames.			#
# 20/06/2018	MG	1.0.5	Remove make, (leave install), of	#
#				libmgec doc-base file as it is now	#
#				built using AC_CONFIG_FILES.		#
# 25/06/2018	MG	1.0.6	Reverse 1.0.5 as AC_CONFIG_FILES cannot	#
#				be used for the substitution of		#
#				Installation Directory Variables.	#
# 10/05/2019	MG	1.1.1	Merge into one project.			#
#									#
#########################################################################


docpkg = $(PACKAGE_TARNAME)-doxy-$(PACKAGE_VERSION).tar.gz

docbasedir = $(datarootdir)/doc-base


# The dependencies below start with Doxyfile which is produced by configure, so
# thereafter no updates to these documents will happen by make alone. Re-run
# configure and make, or, delete the stamp file and run make to force an update.
#

$(docpkg): doxygen.stamp
	tar -chz --format=posix -f $@ html

doxygen.stamp: Doxyfile
	doxygen $<
	echo Timestamp > $@


html_DATA = $(docpkg)

libmgec: Makefile
	mkdir -p $(@D)
	rm -f $@ $@.tmp
	$(edit) $(srcdir)/$(@F).in > $@
libmgec: $(srcdir)/libmgec.in

docbase_DATA = libmgec


# If doc-base is installed register the documents then update dochelp if it is
# installed.
install-data-hook:
	cd $(DESTDIR)$(htmldir) && tar xf $(docpkg)
	if command -v install-docs >/dev/null 2>&1; then \
		install-docs -vi $(docbasedir)/libmgec; \
	fi
	if command -v dochelp >/dev/null 2>&1; then \
		dochelp update; \
	fi

uninstall-hook:
	cd $(DESTDIR)$(htmldir) && rm -rf html
	if command -v install-docs >/dev/null 2>&1; then \
		install-docs -vr libmgec; \
	fi
	if command -v dochelp >/dev/null 2>&1; then \
		dochelp update; \
	fi


EXTRA_DIST = $(docpkg) libmgec.in


CLEANFILES = doxywarn.txt doxygen.stamp $(docpkg) libmgec

clean-local:
	rm -rf html

