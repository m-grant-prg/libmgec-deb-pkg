#########################################################################
#									#
# Author: Copyright (C) 2015-2023  Mark Grant				#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0-only					#
#									#
# Purpose:								#
#	AutoMake script file to generate libmgec project from		#
# source.								#
#									#
#########################################################################


ACLOCAL_AMFLAGS = -I m4 -I m4extra


AM_DISTCHECK_CONFIGURE_FLAGS = --enable-distcheckfake=yes


SUBDIRS = src/man/3/listsandsorts/bstree src/man/3/listsandsorts/sllist
SUBDIRS += src/man/3/listsandsorts/dllist
SUBDIRS += src/man/3/buf-msg src/man/3/errno src/man/3/memory
SUBDIRS += src/prg/c/gen/lib
SUBDIRS += src/prg/c/inc/libmgec
SUBDIRS += src/prg/c/inc-tmp
SUBDIRS += src/prg/c/lib-tmp
SUBDIRS += src/prg/c/pkg-config
SUBDIRS += src/prg/c/src/libmgec
SUBDIRS += src/prg/c/src/test-bstree
SUBDIRS += src/prg/c/src/test-buf-msg
SUBDIRS += src/prg/c/src/test-dllist
SUBDIRS += src/prg/c/src/test-errno
SUBDIRS += src/prg/c/src/test-sllist
SUBDIRS += src/prg/c/src/test-headers
SUBDIRS += src/prg/c/src/run-tests
SUBDIRS += docs/doxygen


doc_DATA = AUTHORS ChangeLog COPYING NEWS README


EXTRA_DIST = $(srcdir)/AUTHORS $(srcdir)/ChangeLog $(srcdir)/COPYING \
		$(srcdir)/NEWS $(srcdir)/README
EXTRA_DIST += m4/gnulib-cache.m4
EXTRA_DIST += docs/misc misc


srctarball:
	@cwd="$${PWD}" && \
	varg="$$(echo @PACKAGE_VERSION@ | sed -e s/\-rc/\~rc/ )" && \
	targ="$${cwd}/@PACKAGE_TARNAME@-$${varg}.tar.gz" && \
	cd @srcdir@ && \
	echo "making srctarball from @srcdir@" && \
	echo "GA	$${targ}" && \
	git archive --format=tar.gz \
		--prefix=@PACKAGE_TARNAME@-$${varg}/ \
		--output=$${targ} \
		HEAD && \
	cd -


doxygen:
	(cd docs/doxygen && rm -f *.stamp && $(MAKE) $(AM_MAKEFLAGS) $@) \
		|| exit 1


.PHONY: doxygen

