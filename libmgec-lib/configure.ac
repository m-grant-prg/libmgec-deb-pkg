#########################################################################
#									#
# Script ID: libmgec-lib/configure.ac					#
# Author: Copyright (C) 2015-2017  Mark Grant				#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0					#
#									#
# Purpose:								#
#	AutoConf script file to configure libmgec project.		#
#									#
# cmd line syntax:							#
# ./configure	[--enable-debug=<yes|no> [default: no]]			#
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
#									#
#########################################################################

AC_REVISION([$Revision: 1.0.18 $])

AC_PREREQ([2.65])


########################
#
# The package version in ac init will be used to create an output variable which
# can be used by ac output and / or the sed setup below to substitute bookmarks
# in source files.
#
########################

AC_INIT([[MGE General C library.]], [v1.1.0],
		[m.grant.prg@gmail.com], [libmgec])

AC_SUBST(pkgversion, $PACKAGE_VERSION)


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

AC_SUBST([tmpheaders])

for entry in `dirname $0`/source/progs/c/inc-tmp/*.h
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

AC_SUBST([tmplibraries])

for direntry in `dirname $0`/source/progs/c/lib-tmp/*
do
	if test -d "$direntry" ;then
		for entry in `dirname $0`\
/source/progs/c/lib-tmp/$(basename "$direntry")/*.la
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

AC_ARG_ENABLE([debug],
	[  --enable-debug    Compile for debugging],
	[case "${enableval}" in
		yes) debug=true ;;
		no)  debug=false ;;
		*) AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
	esac],[debug=false])
AM_CONDITIONAL([DEBUG], [test x$debug = xtrue])

# CFLAGS is usually set to -g -O2, but for debugging we will probably
# want -g -Og and for production we will probably want -O2. So empty CFLAGS here
# and leave the selection to the Makefile.am's.

: ${CFLAGS=""}

if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Build in debug mode.])
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
		-e 's|@pkgversion[@]|\$(pkgversion)|g' \
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
# containing the source.
# This also checks :-	BSD install	make variable set	mkdir -p
#			gawk
if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Running am init automake.])
fi

AM_INIT_AUTOMAKE([-Wall -Werror subdir-objects])

if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Finished running am init automake.])
fi


# Set language for compilation tests.
if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Running ac lang.])
fi

AC_LANG([C])

if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Finished running ac lang.])
fi


# Checks the compiler to use, stores it in the cc variable and checks its
# capabilities.
if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Running ac prog cc.])
fi

AC_PROG_CC

if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Finished running ac prog cc.])
fi


# Checks the c pre-processor to use, stores it in the cpp variable and checks
# its capabilities.
if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Running ac prog cpp.])
fi

AC_PROG_CPP

if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Finished running ac prog cpp.])
fi


# Checks the c++ compiler to use, stores it in the cxx variable and checks its
# capabilities. (Required by ltmain.sh).
if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Running ac prog cxx. (Required by ltmain.sh).])
fi

AC_PROG_CXX

if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Finished running ac prog cxx.])
fi


# Checks that there is an installation program or script.
if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Running ac prog install.])
fi

AC_PROG_INSTALL

if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Finished running ac prog install.])
fi


# Check whether symbolic links are supported.
if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Running ac ln -s.])
fi

AC_PROG_LN_S

if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Finished running ac ln -s.])
fi


# Check a source file to ensure no command line --srcdir typo.
if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Running ac config srcdir.])
fi

AC_CONFIG_SRCDIR([source/progs/c/sysgen/lib/dummy.c])

if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Finished running ac config srcdir.])
fi


# GNULIB macros.
# Also checks for ar, grep, egrep, ranlib and how to run the cpp.
if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Running gl early macro.])
fi

gl_EARLY

if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Finished running gl early macro.])
fi

if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Running gl init macro.])
fi

gl_INIT

if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Finished running gl init macro.])
fi


# Must use this macro if the ar archiver is used. ar is mostly now used for
# static libraries.
if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Running am prog ar.])
fi

AM_PROG_AR

if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Finished running am prog ar.])
fi


# Check for libtool minimum version.
if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Running lt prereq.])
fi

LT_PREREQ([2.4.6])

if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Finished running lt prereq.])
fi


# Turn on shared libraries.
# Also checks for fgrep, linker capabilities, ranlib, sed.
# Also checks for:-	ANSI C header files	sys/types.h	sys/stat.h
#			stdlib.h	string.h	memory.h
#			strings.h	inttypes.h	stdint.h
#			unistd.h	dlfcn.h
if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Running lt init.])
fi

LT_INIT

if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Finished running lt init.])
fi


# Causes AC_OUTPUT to create a c preprocessor file with #define statements about
# the configuration.
if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Running ac config headers.])
fi

AC_CONFIG_HEADERS([source/progs/c/sysgen/inc/config.h])

if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Finished running ac config headers.])
fi


########################
#
# Standard macros will be automatically placed in m4.
# Programmer defined macros should be placed in, say, m4extra which allows us
# to exclude the standard macros from being git tracked. This other directory
# must be specified as an include option in the Makefile.am ACLOCAL_AMFLAGS
#
########################

if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Running ac config macro dir.])
fi


AC_CONFIG_MACRO_DIR([m4])

if test "x${debug}" = xtrue; then
	AC_MSG_NOTICE([Finished running ac config macro dir.])
fi


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

AC_MSG_NOTICE([checking for generic programs required by this application])
AC_CHECK_PROG([TAR], [tar], [yes], [no])
if test "x$TAR" = "xno" ; then
	AC_MSG_ERROR([tar not found])
fi


# Checks for libraries.


# Checks for C header files.
AC_MSG_NOTICE([checking for header files required by this application])
AC_CHECK_HEADERS([stdio.h], [], [AC_MSG_ERROR([header not found])])
AC_CHECK_HEADERS([netdb.h], [], [AC_MSG_ERROR([header not found])])
AC_CHECK_HEADERS([errno.h], [], [AC_MSG_ERROR([header not found])])
AC_CHECK_HEADERS([syslog.h], [], [AC_MSG_ERROR([header not found])])
AC_CHECK_HEADERS([portability.h], [], [AC_MSG_ERROR([header not found])])
AC_CHECK_HEADERS([bstree.h], [], [AC_MSG_ERROR([header not found])])
AC_CHECK_HEADERS([sllist.h], [], [AC_MSG_ERROR([header not found])])
AC_CHECK_HEADERS([dllist.h], [], [AC_MSG_ERROR([header not found])])
AC_CHECK_HEADERS([libmgec.h], [], [AC_MSG_ERROR([header not found])])
AC_CHECK_HEADERS([mgebuffer.h], [], [AC_MSG_ERROR([header not found])])
AC_CHECK_HEADERS([mgemessage.h], [], [AC_MSG_ERROR([header not found])])
AC_CHECK_HEADERS([mgememory.h], [], [AC_MSG_ERROR([header not found])])
AC_CHECK_HEADERS([mge-errno.h], [], [AC_MSG_ERROR([header not found])])


# Checks for C++ header files.


# Checks for typedefs, structures, and compiler characteristics.
AC_MSG_NOTICE([checking for typedefs required by this application])
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T


# Checks for library functions.
AC_MSG_NOTICE([checking for GNU compatible library functions required by this \
application])
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset strerror])


# Project Makefiles to create.
AC_CONFIG_FILES([Makefile
		source/progs/c/sysgen/inc/Makefile
		source/progs/c/sysgen/lib/Makefile
		source/progs/c/inc-tmp/Makefile
		source/progs/c/lib-tmp/Makefile
		source/progs/c/src/libmgec/Makefile
		source/progs/c/src/test-bstree/Makefile
		source/progs/c/src/test-dllist/Makefile
		source/progs/c/src/test-errno/Makefile
		source/progs/c/src/test-sllist/Makefile])


AC_OUTPUT
