#########################################################################
#									#
# Script ID: lib/configure.ac						#
# Author: Copyright (C) 2015-2018  Mark Grant				#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0					#
#									#
# Purpose:								#
#	AutoConf script file to configure libmgec project.		#
#									#
# cmd line syntax:							#
# ./configure	[--enable-debug=<yes|no> [default: no]]			#
#		[--enable-headercheck=<yes|no> [default: no]]		#
#		[--enable-sparse=<yes|no> [default: no]]		#
#									#
#########################################################################

#########################################################################
#									#
# Changelog								#
#									#
# Date		Author	Version	Description				#
#									#
# 07/08/2015	MG	1.0.1	First release.				#
# 26/08/2015	MG	1.0.2	Remove redundant check for errno.h	#
# 25/10/2015	MG	1.0.3	Restructure and change to conform to	#
#				AutoTools General Template v1.0.6.	#
# 03/11/2015	MG	1.0.4	Change from bt and btree names to bst	#
#				and bstree as this is a binary search	#
#				tree, not a b-tree.			#
# 03/05/2016	MG	1.0.5	Add build of sllist test suite and	#
#				checks for header files.		#
# 06/05/2016	MG	1.0.6	Add build of dllist test suite and	#
#				checks for header files.		#
# 15/11/2016	MG	1.0.7	Add checks for buffer, memory and	#
#				message headers.			#
# 13/01/2017	MG	1.0.8	Change to empty CFLAGS here and leave	#
#				setting to the Makefile.am's.		#
# 24/01/2017	MG	1.0.9	Add build of errno test suite.		#
#				Remove test for listsandsorts.h and add	#
#				test for mge-errno.h.			#
# 29/01/2017	MG	1.0.10	Correct header file checks.		#
# 12/03/2017	MG	1.0.11	Adopt new code formatting.		#
# 25/03/2017	MG	1.0.12	Add support for temporary header	#
#				directory.				#
# 26/03/2017	MG	1.0.13	Tidy AC_INIT and pkgversion AC_SUBST	#
#				onto multiple lines.			#
# 03/04/2017	MG	1.0.14	Add non-distribution header directory.	#
# 09/06/2017	MG	1.0.15	Add support for temporary libraries.	#
# 18/10/2017	MG	1.0.16	Add search for temporary libraries and	#
#				store result in a variable for AutoMake	#
#				consumption.				#
# 10/12/2017	MG	1.0.17	Add SPDX license tags to source files.	#
# 23/12/2017	MG	1.0.18	Change to manual package version	#
#				numbering on adoption of project /	#
#				sub-project structure.			#
# 02/01/2018	MG	1.0.19	Move to new source directory structure.	#
# 09/01/2018	MG	1.0.20	Correct generation of config.h		#
# 17/01/2018	MG	1.0.21	Update minimum AutoTools version.	#
# 11/02/2018	MG	1.0.22	Make AutoMake use posix format for tar.	#
# 26/03/2018	MG	1.0.23	Add support for an enable-sparse CLA	#
#				and passing a suitable variable to the	#
#				Makefile.am's.				#
# 20/06/2018	MG	1.0.24	Use better source file to check source	#
#				directory in AC_CONFIG_SRCDIR.		#
#				AC_DEFINE SOURCE_VERSION for use in	#
#				version.c via config.h			#
#				Remove pkgversion AC_SUBST as it is	#
#				available via AC_CONFIG_HEADERS and	#
#				AC_CONFIG_FILES from AC_INIT info.	#
#				AC_SUBST the lib_version_info so that	#
#				all top level versioning can be done	#
#				from configure.ac			#
# 08/08/2018	MG	1.0.25	Add check for stdbool.h			#
#				Add support for an enable-headercheck	#
#				CLA and passing a suitable variable to	#
#				the Makefile.am's.			#
#				Build suitable CFLAGS based on compiler	#
#				version.				#
# 06/09/2018	MG	1.0.26	Add buffers and messages test program.	#
# 09/09/2018	MG	1.0.27	Add build for inc directory.		#
#									#
#########################################################################

AC_REVISION($Revision: 1.0.27 $)

AC_PREREQ(2.69)


########################
#
# The following macros set all top level versioning for this project. All
# information can be propagated via AC_CONFIG_HEADERS and AC_CONFIG_FILES.
#
########################

AC_INIT(MGE General C Library, v1.1.9-rc2, m.grant.prg@gmail.com, libmgec)

AC_DEFINE(SOURCE_VERSION, "1.1.7", \
	Define to the version of source code in this package.)

AC_SUBST(lib_version_info, "1:0:0")


########################
#
# This creates an AutoConf substitution variable for temporary header files.
# Temporary headers might be copies of -dev package header files brought into a
# library package for development and modification. Whilst there it should be
# used. When finished it must be moved back to the -dev package for release.
# This variable and the inc-tmp/Makefile.am allow for this conditional use and
# even conditional presence in inc-tmp.
# The use of `dirname $0` to get the configure invocation directory is critical
# for parallel builds and make distcheck as the relative path always stays the
# same but configure may be invoked from different directories.
#
########################

AC_SUBST(tmpheaders)

for entry in `dirname $0`/src/prg/c/inc-tmp/*.h
do
	if test -f "$entry" ;then
		tmpheaders=$tmpheaders" "$(basename "$entry")
	fi
done


########################
#
# This creates an AutoConf substitution variable for temporary libraries.
# Temporary libraries are development copies of libraries from other packages
# which are being tested / modified in conjunction with this package.
# This variable can be consumed in the AutoMake XXX_LDADD line.
# The use of `dirname $0` to get the configure invocation directory is critical
# for parallel builds and make distcheck as the relative path always stays the
# same but configure may be invoked from different directories.
#
########################

AC_SUBST(tmplibraries)

for direntry in `dirname $0`/src/prg/c/lib-tmp/*
do
	if test -d "$direntry" ;then
		for entry in `dirname $0`\
/src/prg/c/lib-tmp/$(basename "$direntry")/*.la
		do
			if test -f "$entry" ;then
				tmplibraries=$tmplibraries\
" \$(srcdir)/../../lib-tmp/"$(basename "$direntry")"/"$(basename "$entry")
			fi
		done
	fi
done


########################
#
# The following allows for an enable-debug=yes/no command line option. The
# conditional DEBUG is made available to the makefiles.
#
########################

AC_ARG_ENABLE(debug,
	--enable-debug    Compile for debugging,
	[case "${enableval}" in
		yes) debug=true ;;
		no)  debug=false ;;
		*) AC_MSG_ERROR(bad value ${enableval} for --enable-debug) ;;
	esac],debug=false)
AM_CONDITIONAL(DEBUG, test x$debug = xtrue)

# CFLAGS is usually set to -g -O2, but for debugging we will probably
# want -g -Og and for production we will probably want -O2. So empty CFLAGS here
# and leave the selection to the Makefile.am's.

: ${CFLAGS=""}

if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE(Build in debug mode.)
fi


########################
#
# The following allows for an enable-headercheck=yes/no command line option.
# The conditional HEADERCHECK is made available to the makefiles.
#
########################

AC_ARG_ENABLE(headercheck,
	--enable-headercheck    Build to display include stack,
	[case "${enableval}" in
		yes) headercheck=true ;;
		no)  headercheck=false ;;
		*) AC_MSG_ERROR(bad value ${enableval} in enable-headercheck);;
	esac],headercheck=false)
AM_CONDITIONAL(HEADERCHECK, test x$headercheck = xtrue)

if test "x${headercheck}" = xtrue; then
	AC_MSG_NOTICE(Building to display include stack depth.)
fi


########################
#
# The following allows for an enable-sparse=yes/no command line option. The
# conditional SPARSE is made available to the makefiles.
#
########################

AC_ARG_ENABLE(sparse,
	--enable-sparse    Build with sparse,
	[case "${enableval}" in
		yes) sparse=true ;;
		no)  sparse=false ;;
		*) AC_MSG_ERROR(bad value ${enableval} for --enable-sparse);;
	esac],sparse=false)
AM_CONDITIONAL(SPARSE, test x$sparse = xtrue)

if test "x${sparse}" = xtrue; then
	AC_MSG_NOTICE(Building using sparse.)
fi


########################
#
# Now set up a sed sequence to substitute bookmarks in script files with either
# standard GNU Directory Variables, or with programmer-defined variables set up
# using an AC_SUBST macro above. This sed sequence will be invoked at programmer
# discretion at sub-directory Makefile.am level.
# ----------------------
#
# prefix	/usr/local (typically)
#	exec_prefix	${prefix}
#		bindir	${exec_prefix}/bin	user executables
#		sbindir	${exec_prefix}/sbin	system admin executables
#		libexecdir	${exec_prefix}/libexec	program executables
#		libdir	${exec_prefix}/lib	object code libraries
#	sysconfdir	 ${prefix}/etc	read-only single-machine data
#	sharedstatedir	${prefix}/com	modifiable architecture-independent data
#	localstatedir	${prefix}/var	modifiable single-machine data
#	runstatedir	${localstatedir}/run
#	includedir	${prefix}/include	C header files
#	oldincludedir	$usr/include	C header files
#	datarootdir	${prefix}/share	read-only arch.-independent data root
#		localedir	${datarootdir}/locale	locale-dependent data
#		datadir	${datarootdir}	read-only architecture-independent data
#		mandir	${datarootdir}/man	man documentation
#		infodir	${datarootdir}/info	info documentation
#		docdir	${datarootdir}/doc/${PACKAGE}	documentation root
#			htmldir	${docdir}	html documentation
#			dvidir	${docdir}	dvi documentation
#			pdfdir	${docdir}	pdf documentation
#			psdir	${docdir}	ps documentation
#		lispdir	${datarootdir}/emacs/site-lisp
#	pkgdatadir	${datarootdir}/${PACKAGE}
#	pkgincludedir	${includedir}/${PACKAGE}
#	pkglibdir	${libdir}/${PACKAGE}
#	pkglibexecdir	${libexecdir}/${PACKAGE}
#
########################

AC_SUBST([edit], ["sed \
		-e 's|@prefix[@]|\$(prefix)|g' \
		-e 's|@exec_prefix[@]|\$(exec_prefix)|g' \
		-e 's|@bindir[@]|\$(bindir)|g' \
		-e 's|@sbindir[@]|\$(sbindir)|g' \
		-e 's|@libexecdir[@]|\$(libexecdir)|g' \
		-e 's|@libdir[@]|\$(libdir)|g' \
		-e 's|@sysconfdir[@]|\$(sysconfdir)|g' \
		-e 's|@sharedstatedir[@]|\$(sharedstatedir)|g' \
		-e 's|@localstatedir[@]|\$(localstatedir)|g' \
		-e 's|@runstatedir[@]|\$(runstatedir)|g' \
		-e 's|@includedir[@]|\$(includedir)|g' \
		-e 's|@oldincludedir[@]|\$(oldincludedir)|g' \
		-e 's|@datarootdir[@]|\$(datarootdir)|g' \
		-e 's|@localedir[@]|\$(localedir)|g' \
		-e 's|@datadir[@]|\$(datadir)|g' \
		-e 's|@mandir[@]|\$(mandir)|g' \
		-e 's|@infodir[@]|\$(infodir)|g' \
		-e 's|@docdir[@]|\$(docdir)|g' \
		-e 's|@htmldir[@]|\$(htmldir)|g' \
		-e 's|@dvidir[@]|\$(dvidir)|g' \
		-e 's|@pdfdir[@]|\$(pdfdir)|g' \
		-e 's|@psdir[@]|\$(psdir)|g' \
		-e 's|@lispdir[@]|\$(lispdir)|g' \
		-e 's|@pkgdatadir[@]|\$(pkgdatadir)|g' \
		-e 's|@pkgincludedir[@]|\$(pkgincludedir)|g' \
		-e 's|@pkglibdir[@]|\$(pkglibdir)|g' \
		-e 's|@pkglibexecdir[@]|\$(pkglibexecdir)|g'"])


# Passes the options to all am files. Puts objects in the sub-directory
# containing the source. Forces tar to use --format=posix in make dist.
# This also checks :-	BSD install	make variable set	mkdir -p
#			gawk
AM_INIT_AUTOMAKE(-Wall -Werror subdir-objects tar-pax)


# Set language for compilation tests.
AC_LANG(C)


# Checks the compiler to use from either a standard list or one to use for
# sparse, stores it in the CC variable and checks its capabilities.
if test "x$sparse" = "xtrue" ; then
	compiler_list="cgcc gcc cc"
else
	compiler_list="gcc cc"
fi

AC_PROG_CC($compiler_list)


# Checks the c pre-processor to use, stores it in the cpp variable and checks
# its capabilities.
AC_PROG_CPP


# Build a suitable CFLAGS list depending on compiler version.
# This has been checked up to gcc v8.2
AC_SUBST(mg_cflags)
AX_COMPILER_VENDOR
AX_COMPILER_VERSION
# The following 2 options seem fairly universal.
mg_cflags="-Wall -Wextra"
if test "$ax_cv_c_compiler_vendor" = "gnu"; then
	mg_cflags+=" -Wmissing-include-dirs -Wshadow -Wstrict-prototypes"
	AX_COMPARE_VERSION($ax_cv_c_compiler_version, ge, "7")
	if test "x${ax_compare_version}" = xtrue; then
		mg_cflags+=" -Wimplicit-fallthrough"
	fi
fi


# Checks the c++ compiler to use, stores it in the cxx variable and checks its
# capabilities. (Required by ltmain.sh).
AC_PROG_CXX


# Checks that there is an installation program or script.
AC_PROG_INSTALL


# Check whether symbolic links are supported.
AC_PROG_LN_S


# Check a source file to ensure no command line --srcdir typo.
AC_CONFIG_SRCDIR(src/prg/c/src/libmgec/version.c)


# GNULIB macros.
# Also checks for ar, grep, egrep, ranlib and how to run the cpp.
gl_EARLY

gl_INIT


# Must use this macro if the ar archiver is used. ar is mostly now used for
# static libraries.
AM_PROG_AR


# Check for libtool minimum version.
LT_PREREQ(2.4.6)


# Turn on shared libraries.
# Also checks for fgrep, linker capabilities, ranlib, sed.
# Also checks for:-	ANSI C header files	sys/types.h	sys/stat.h
#			stdlib.h	string.h	memory.h
#			strings.h	inttypes.h	stdint.h
#			unistd.h	dlfcn.h
LT_INIT


# Causes AC_OUTPUT to create a c preprocessor file with #define statements about
# the configuration.
AC_CONFIG_HEADERS(src/prg/c/gen/inc/config.h)


########################
#
# Standard macros will be automatically placed in m4.
# Programmer defined macros should be placed in, say, m4extra which allows us
# to exclude the standard macros from being git tracked. This other directory
# must be specified as an include option in the Makefile.am ACLOCAL_AMFLAGS
# e.g.
# ACLOCAL_AMFLAGS = -I m4 -I m4extra
#
########################

AC_CONFIG_MACRO_DIR(m4)


########################
#
# Checks for programs.
# If using am init automake, gl early or lt init the following programs are
# automatically checked:-
#
# am init automake
#	BSD install	mkdir -p	gawk
#
# gl early
#	ar	grep	egrep	ranlib
#
# lt init
#	fgrep	ranlib	sed
#
# Particular and generic program checks follow:
#
########################

AC_MSG_NOTICE(checking for generic programs required by this application)
AC_CHECK_PROG(TAR, tar, yes, no)
if test "x$TAR" = "xno" ; then
	AC_MSG_ERROR(tar not found)
fi


# Checks for libraries.


# Checks for C header files.
AC_MSG_NOTICE(checking for header files required by this application)
AC_CHECK_HEADERS(stdio.h, [], AC_MSG_ERROR(header not found))
AC_CHECK_HEADERS(netdb.h, [], AC_MSG_ERROR(header not found))
AC_CHECK_HEADERS(errno.h, [], AC_MSG_ERROR(header not found))
AC_CHECK_HEADERS(syslog.h, [], AC_MSG_ERROR(header not found))
AC_CHECK_HEADERS(stdbool.h, [], AC_MSG_ERROR(header not found))
AC_CHECK_HEADERS(portability.h, [], AC_MSG_ERROR(header not found))
AC_CHECK_HEADERS(bstree.h, [], AC_MSG_ERROR(header not found))
AC_CHECK_HEADERS(sllist.h, [], AC_MSG_ERROR(header not found))
AC_CHECK_HEADERS(dllist.h, [], AC_MSG_ERROR(header not found))
AC_CHECK_HEADERS(libmgec.h, [], AC_MSG_ERROR(header not found))
AC_CHECK_HEADERS(mgebuffer.h, [], AC_MSG_ERROR(header not found))
AC_CHECK_HEADERS(mgemessage.h, [], AC_MSG_ERROR(header not found))
AC_CHECK_HEADERS(mgememory.h, [], AC_MSG_ERROR(header not found))
AC_CHECK_HEADERS(mge-errno.h, [], AC_MSG_ERROR(header not found))


# Checks for C++ header files.


# Checks for typedefs, structures, and compiler characteristics.
AC_MSG_NOTICE(checking for typedefs required by this application)
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T


# Checks for library functions.
AC_MSG_NOTICE(checking for GNU compatible library functions required by this \
application)
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS(memset strerror)


# Project Makefiles to create.
AC_CONFIG_FILES(Makefile
		src/prg/c/gen/lib/Makefile
		src/prg/c/inc/Makefile
		src/prg/c/inc-tmp/Makefile
		src/prg/c/lib-tmp/Makefile
		src/prg/c/src/libmgec/Makefile
		src/prg/c/src/test-bstree/Makefile
		src/prg/c/src/test-buf-msg/Makefile
		src/prg/c/src/test-dllist/Makefile
		src/prg/c/src/test-errno/Makefile
		src/prg/c/src/test-sllist/Makefile)


AC_OUTPUT
