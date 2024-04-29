#########################################################################
#									#
# Author: Copyright (C) 2017-2023  Mark Grant				#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0-only					#
#									#
# Purpose:								#
#	AutoMake script file to produce doxygen html documentation.	#
#									#
#########################################################################


srcdepends := $(shell find $(srcdir)/src -type f -printf "%p ") \
	$(shell find $(top_srcdir) -type f -name *.c -printf "%p " \
		-o -name *.h -printf "%p ")


# Build API documentation.

docpkg = $(PACKAGE_TARNAME)-doxy-$(PACKAGE_VERSION).tar.gz

$(docpkg): doxygen.stamp
	tar -chz --format=posix -f $@ html

doxygen.stamp: Doxyfile $(srcdepends)
	cd $(srcdir)/gen-img/buf-msg \
		&& dia ../../src/buf-msg/*.dia --filter=png \
		&& cd -
	if $(AM_V_P); then \
		DOXYGEN_QUIET=NO \
			DOXYGEN_PROJECT_NAME="MGE General C Library - API Documentation" \
			DOXYGEN_HTML_OUTPUT=html \
			DOXYGEN_ENABLED_SECTIONS= \
			DOXYGEN_EXCLUDE_PATTERNS="*internal*" \
			doxygen $< ; \
	else \
		DOXYGEN_QUIET=YES \
			DOXYGEN_PROJECT_NAME="MGE General C Library - API Documentation" \
			DOXYGEN_HTML_OUTPUT=html \
			DOXYGEN_ENABLED_SECTIONS= \
			DOXYGEN_EXCLUDE_PATTERNS="*internal*" \
			doxygen $< ; \
	fi
	rm -f $(srcdir)/gen-img/buf-msg/*
	echo Timestamp > $@


# Build full internal documentation.

intdocpkg = $(PACKAGE_TARNAME)-int-doxy-$(PACKAGE_VERSION).tar.gz

$(intdocpkg): doxygen1.stamp
	tar -chz --format=posix -f $@ html-int

doxygen1.stamp: Doxyfile $(srcdepends)
	cd $(srcdir)/gen-img/buf-msg \
		&& dia ../../src/buf-msg/*.dia --filter=png \
		&& cd -
	if $(AM_V_P); then \
		DOXYGEN_QUIET=NO \
			DOXYGEN_PROJECT_NAME="MGE General C Library - Full Internal Documentation" \
			DOXYGEN_HTML_OUTPUT=html-int \
			DOXYGEN_ENABLED_SECTIONS=INTERNAL \
			DOXYGEN_EXCLUDE_PATTERNS= \
			doxygen $< ; \
	else \
		DOXYGEN_QUIET=YES \
			DOXYGEN_PROJECT_NAME="MGE General C Library - Full Internal Documentation" \
			DOXYGEN_HTML_OUTPUT=html-int \
			DOXYGEN_ENABLED_SECTIONS=INTERNAL \
			DOXYGEN_EXCLUDE_PATTERNS= \
			doxygen $< ; \
	fi
	rm -rf $(srcdir)/gen-img/buf-msg/*
	echo Timestamp > $@


# Create a target to facilitate make doxygen
doxygen: $(docpkg) $(intdocpkg) libmgec libmgec-int

.PHONY: doxygen


apidir = $(htmldir)/api
intdir = $(htmldir)/int

api_DATA = $(docpkg)
int_DATA = $(intdocpkg)


libmgec libmgec-int: Makefile
	mkdir -p $(@D)
	rm -f $@ $@.tmp
	$(edit) $(srcdir)/$(@F).in > $@
libmgec: $(srcdir)/libmgec.in
libmgec-int: $(srcdir)/libmgec-int.in


# If doc-base is installed register the documents then update dochelp if it is
# installed. Registering is dependent on ATONLY.

docbasedir = @docbaseloc@

docbase_DATA = libmgec libmgec-int

install-data-hook:
if !DISTCHECKFAKE
	cd $(DESTDIR)$(apidir) && tar xf $(docpkg)
	cd $(DESTDIR)$(intdir) && tar xf $(intdocpkg)
if ATONLY
	if command -v install-docs >/dev/null 2>&1; then \
		install-docs -vi $(docbasedir)/libmgec; \
		install-docs -vi $(docbasedir)/libmgec-int; \
	fi
	if command -v dochelp >/dev/null 2>&1; then \
		dochelp update; \
	fi
endif
endif

uninstall-local:
if !DISTCHECKFAKE
if ATONLY
	if command -v install-docs >/dev/null 2>&1; then \
		install-docs -vr libmgec; \
		install-docs -vr libmgec-int; \
	fi
	if command -v dochelp >/dev/null 2>&1; then \
		dochelp update; \
	fi
endif
	cd $(DESTDIR)$(apidir) && rm -rf html
	cd $(DESTDIR)$(intdir) && rm -rf html-int
endif


EXTRA_DIST = $(docpkg) $(intdocpkg) $(srcdir)/src $(srcdir)/gen-img \
	     $(srcdir)/libmgec.in $(srcdir)/libmgec-int.in


CLEANFILES = doxywarn.txt doxygen.stamp doxygen1.stamp libmgec libmgec-int

clean-local:
	rm -rf html html-int libmgec*doxy*.tar.gz

