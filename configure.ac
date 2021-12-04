#########################################################################
#									#
# Script ID: ./configure.ac						#
# Author: Copyright (C) 2015-2021  Mark Grant				#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0-only					#
#									#
# Purpose:								#
#	AutoConf script file to configure libmgec project.		#
#									#
# cmd line syntax:							#
# ./configure	[--enable-atonly=<yes|no> [default: no]]		#
#		[--enable-debug=<yes|no> [default: no]]			#
#		[--enable-distcheckfake=<yes|no> [default: no]]		#
#		[--enable-headercheck=<yes|no> [default: no]]		#
#		[--enable-sparse=<yes|no> [default: no]]		#
#									#
# Parameters generic description. For specifics to this configure.ac	#
# please see inline comments at the point of definition:-		#
# --enable-atonly							#
#	Used to produce a fully working package just from the AT build	#
#	when the build references a (distro / external) static location	#
#	eg another package's config file in /etc (AOT AT's		#
#	/usr/local/etc), or an externally installed jar file in		#
#	/usr/share/jave (AOT AT's /usr/local/share/java).		#
# --enable-debug							#
#	Used to set things like compiler debug flags.			#
# --enable-distcheckfake						#
#	Enables the replacement of an absolute directory path specified	#
#	in a variable, with a value based on AutoTools standard		#
#	directories. This enables the Makefile.am to use the AT		#
#	variable based value when running distcheck and the absolute	#
#	path for all else. Hence distcheck can now succeed when it	#
#	would normally fail.						#
# --enable-headercheck							#
#	Used to set a flag to output the header file nesting.		#
# --enable-sparse							#
#	Used to compile with the sparse static analyser.		#
#									#
# Layout: (Only relevant sections will exist).				#
# ChangeLog : High level ChangeLog					#
# SECTION  1: Initialisation & Setup					#
# SECTION  2: Architecture, target and host checks			#
# SECTION  3: Command line arguments					#
# SECTION  4: Compiler setup						#
# SECTION  5: Check for programs					#
# SECTION  6: Check for libraries					#
# SECTION  7: Check for header files					#
# SECTION  8: Check for types						#
# SECTION  9: Check for structures					#
# SECTION 10: Check for compiler characteristics			#
# SECTION 11: Check for library functions				#
# SECTION 12: Check for pkg-config files				#
# SECTION 13: Check for system services					#
# SECTION 14: Additional checks & variables				#
# SECTION 15: Specify the output files					#
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
# 10/02/2019	MG	1.0.28	Extract compiler-dependent CFLAGS build	#
#				to m4extra macro.			#
# 18/05/2019	MG	1.1.1	Remove v from package vesrion.		#
#				Revamp to new standard layout.		#
#				Merge dev sub-project.			#
#				Merge doc sub-project.			#
# 01/06/2019	MG	1.1.2	Use standard macro AC_HEADER_STDBOOL 	#
#				in preference to AC_CHECK_HEADERS.	#
#				Add missing header checks.		#
# 28/06/2019	MG	1.1.3	Add directory to run make check tests.	#
#				Correct ARG_ENABLE help text.		#
#				Add enable-distcheckfake option.	#
#				Add enable option descriptions in this	#
#				file's header.				#
# 20/07/2020	MG	1.1.4	Merge buffer and message man pages.	#
#				Move lists and sorts man pages under	#
#				that directory.				#
# 15/04/2021	MG	1.1.5	Add support for passing some default	#
#				values to Makefiles.am.			#
# 25/05/2021	MG	1.1.6	Add check for dialog and emit warning.	#
#				dialog can be used by bootstrap.sh -m.	#
# 26/07/2021	MG	1.1.7	Make use of new CPPFLAGS macro.		#
#				Make use of new LDFLAGS macro.		#
# 14/09/2021	MG	1.1.8	Add enable-atonly CLA and add support	#
#				for doc-base.				#
# 05/11/2021	MG	1.1.9	Create debug version of flags where	#
# 03/12/2021	MG	1.1.10	If git is available and we are inside a	#
#				git tree then use git describe to add	#
#				further package version information.	#
#				Add AC_COPYRIGHT macro.			#
#				Tighten SPDX tag.			#
#									#
#########################################################################


#########################################
#					#
# SECTION  1: Initialisation & Setup	#
#					#
#########################################

AC_COPYRIGHT([Copyright (C) 2015-2021  Mark Grant
	      This script is free to copy or distribute under the terms set out
	      in the package license. See COPYING for details.])

AC_REVISION($Revision: 1.1.10 $)

AC_PREREQ(2.69)

#
# The following macro uses git, if available, to provide versioning information.
# The logic is as follows:-
# If git is not available, is not initialised or no commit has been made, then
# the local variable pkg_version will be used.
# If git is available but no Tag has been created then just a commit identifier
# will be used.
# If git is available and a tag has been created then the most recent tag, plus
# number of commits since the tag, plus a commit identifier will be used.
# The package version in ac init will be used to create an output variable which
# can be used by ac output and / or the sed setup below to substitute bookmarks
# in source files.
#
# Set pkg_version for a default hard-coded version number.
m4_define(pkg_version, 1.5.2)

AC_INIT([MGE General C Library], m4_esyscmd([ \
	git describe --always 1>/dev/null 2>/dev/null \
	&& sed --help 1>/dev/null 2>/dev/null \
	&& git describe --always | sed 's/v//' | tr -d '\n' \
	|| echo pkg_version | tr -d '\n']),
	[m.grant.prg@gmail.com], [libmgec])

AC_MSG_NOTICE(initialisation and setup)

AC_DEFINE(SOURCE_VERSION, "1.2.4", \
	Define to the version of source code in this package.)

AC_SUBST(lib_version_info, "5:0:3")

#
# Passes the options to all am files. Puts objects in the sub-directory
# containing the source. Forces tar to use --format=posix in make dist.
# This also checks :-	BSD install	make variable set	mkdir -p
#			gawk
#
AM_INIT_AUTOMAKE([-Wall -Werror subdir-objects tar-pax])

#
# Standard macros will be automatically placed in m4.
# Programmer defined macros should be placed in, say, m4extra which allows us
# to exclude the standard macros from being git tracked. This other directory
# must be specified as an include option in the Makefile.am ACLOCAL_AMFLAGS
# e.g.
# ACLOCAL_AMFLAGS = -I m4 -I m4extra
#
AC_CONFIG_MACRO_DIR([m4])


#########################################
#					#
# SECTION  3: Command line arguments	#
#					#
#########################################

AC_MSG_NOTICE(checking command line arguments)

#
# The following allows for an enable-atonly=yes/no command line option. The
# conditional ATONLY is made available to the makefiles.
# This allows for a workaround where AutoTools normally has a prefix of
# /usr/local but anything pre-installed would normally be in /usr.
#
AC_ARG_ENABLE(atonly,
	AS_HELP_STRING([--enable-atonly], \
			[build for AT only testing or installation]),
	[case "${enableval}" in
		yes) atonly=true ;;
		no)  atonly=false ;;
		*) AC_MSG_ERROR(bad value ${enableval} for --enable-atonly) ;;
	esac],atonly=false)
AM_CONDITIONAL(ATONLY, test x$atonly = xtrue)

if test "x${atonly}" = xtrue; then
	AC_MSG_NOTICE(building for AT only testing or installing)
	AC_SUBST(docbaseloc,"/usr/share/doc-base")
else
	AC_SUBST(docbaseloc,"$datarootdir/doc-base")
fi

#
# The following allows for an enable-debug=yes/no command line option. The
# conditional DEBUG is made available to the makefiles.
#
AC_ARG_ENABLE(debug,
	AS_HELP_STRING([--enable-debug], [compile for debugging]),
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
	AC_MSG_NOTICE(build in debug mode)
fi

#
# If a file location has to be fixed, e.g. /etc/foo.conf and never
# /usr/local/etc/foo.conf, then make distcheck will fail. Setting this flag
# allows make distcheck to locate the file in an AT standard directory-based
# location.
# eg /usr/local/etc/foo.conf.
# and hence succeed.
#
AC_ARG_ENABLE([distcheckfake],
	AS_HELP_STRING([--enable-distcheckfake], [enable running of distcheck]),
	[case "${enableval}" in
		yes) distcheckfake=true ;;
		no)  distcheckfake=false ;;
		*) AC_MSG_ERROR([bad value ${enableval} for \
			--enable-distcheckfake]) ;;
	esac],[distcheckfake=false])
AM_CONDITIONAL([DISTCHECKFAKE], [test x$distcheckfake = xtrue])

if test "x${distcheckfake}" = xtrue; then
	AC_MSG_NOTICE([using workarounds to facilitate distcheck])
else
	AC_MSG_NOTICE([using distcheck incompatible setup])
fi

#
# The following allows for an enable-headercheck=yes/no command line option.
# The conditional HEADERCHECK is made available to the makefiles.
#
AC_ARG_ENABLE(headercheck,
	AS_HELP_STRING([--enable-headercheck], [build to display header stack]),
	[case "${enableval}" in
		yes) headercheck=true ;;
		no)  headercheck=false ;;
		*) AC_MSG_ERROR(bad value ${enableval} in enable-headercheck);;
	esac],headercheck=false)
AM_CONDITIONAL(HEADERCHECK, test x$headercheck = xtrue)

if test "x${headercheck}" = xtrue; then
	AC_MSG_NOTICE(building to display include stack depth)
fi

#
# The following allows for an enable-sparse=yes/no command line option. The
# conditional SPARSE is made available to the makefiles.
#
AC_ARG_ENABLE(sparse,
	AS_HELP_STRING([--enable-sparse], [build with sparse]),
	[case "${enableval}" in
		yes) sparse=true ;;
		no)  sparse=false ;;
		*) AC_MSG_ERROR(bad value ${enableval} for --enable-sparse);;
	esac],sparse=false)
AM_CONDITIONAL(SPARSE, test x$sparse = xtrue)

if test "x${sparse}" = xtrue; then
	AC_MSG_NOTICE(building using sparse)
fi

# Pass on some CLA default values to Makefile.am
AC_SUBST(DEF_CPP_VALUES, $CLA_DEF_CPP_VALUES)


#################################
#				#
# SECTION  4: Compiler setup	#
#				#
#################################

AC_MSG_NOTICE([checking compiler setup])

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

# GNULIB gl_EARLY macro. Place just after AC_PROG_CC.
# Also checks for ar, grep, egrep, ranlib and how to run the cpp.
gl_EARLY

# Checks the c pre-processor to use, stores it in the cpp variable and checks
# its capabilities.
AC_PROG_CPP

# Checks the c++ compiler to use, stores it in the cxx variable and checks its
# capabilities. (Required by ltmain.sh).
AC_PROG_CXX

# GNULIB gl_INIT macro. Must appear after other checks which may affect the
# compiler invocation.
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


#########################################
#					#
# SECTION  5: Check for programs	#
#					#
#########################################

AC_MSG_NOTICE(checking for basic programs that have AutoConf checks)

#
# The small set of tools you can expect to find on any machine.
#
# awk		date		grep		od
# basename	diff		join		rm
# cat		dirname		ln		rmdir
# cc		egrep		ls		sed
# chgrp		expr		mkdir		sleep
# chown		expr (‘|’)	mkfifo		sort
# chmod		expr (‘:’)	mknod		tar
# cmp		fgrep		mktemp		touch
# cp		find		mv		tr
#
# (For further information including limitations to the above, see Section 11.15
# in the GNU AutoConf Manual).
#
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
# Basic and AutoTools program checks.
#
AC_PROG_AWK
AC_PROG_EGREP
AC_PROG_FGREP
AC_PROG_GREP
AC_PROG_LN_S
AC_PROG_MKDIR_P
AC_PROG_SED

AC_MSG_NOTICE(checking for some standard AutoTools required programs)
AC_PROG_INSTALL

AC_MSG_NOTICE(checking for particular programs required by this build)
AC_CHECK_PROG(DIA, dia, yes, no)
if test "x$DIA" = "xno" ; then
	AC_MSG_ERROR(dia not found)
fi

AC_CHECK_PROG(DIALOG, dialog, yes, no)
if test "x$DIALOG" = "xno" ; then
	AC_MSG_WARN(dialog  not found - could be needed at build time)
fi

AC_CHECK_PROG(DOT, dot, yes, no)
if test "x$DOT" = "xno" ; then
	AC_MSG_ERROR(dot not found)
fi

AC_CHECK_PROG(DOXYGEN, doxygen, yes, no)
if test "x$DOXYGEN" = "xno" ; then
	AC_MSG_ERROR(doxygen not found)
fi

AC_CHECK_PROG([TAR], [tar], [yes], [no])
if test "x$TAR" = "xno" ; then
	AC_MSG_ERROR([tar not found])
fi

AC_CHECK_PROG([TXT2MAN], [txt2man], [yes], [no])
if test "x$TXT2MAN" = "xno" ; then
	AC_MSG_ERROR([txt2man not found])
fi

AC_CHECK_PROG([TXT2MANWRAP], [txt2manwrap], [yes], [no])
if test "x$TXT2MANWRAP" = "xno" ; then
	AC_MSG_ERROR([txt2manwrap not found])
fi

AC_MSG_NOTICE(checking for particular programs required at build and run time)

AC_MSG_NOTICE(checking for particular programs required at run time)


#########################################
#					#
# SECTION  7: Check for header files	#
#					#
#########################################

AC_MSG_NOTICE(checking for header files required by this application)

AC_CHECK_HEADERS(stdio.h, [], AC_MSG_ERROR(header not found))
AC_CHECK_HEADERS(stdlib.h, [], AC_MSG_ERROR(header not found))
AC_CHECK_HEADERS(string.h, [], AC_MSG_ERROR(header not found))
AC_CHECK_HEADERS(netdb.h, [], AC_MSG_ERROR(header not found))
AC_CHECK_HEADERS(errno.h, [], AC_MSG_ERROR(header not found))
AC_CHECK_HEADERS(sys/types.h, [], AC_MSG_ERROR(header not found))
AC_CHECK_HEADERS(syslog.h, [], AC_MSG_ERROR(header not found))

AC_HEADER_STDBOOL


#################################
#				#
# SECTION  8: Check for types	#
#				#
#################################

AC_MSG_NOTICE(checking for typedefs required by this application)
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T


#########################################################
#							#
# SECTION 10: Check for compiler characteristics	#
#							#
#########################################################

AC_MSG_NOTICE(checking for compiler characteristics)

# Build suitable pre-processor, compiler and linker flags.
BUILD_COMPILER_VERSION_CPPFLAGS(MG_CPPFLAGS, MG_DEBUG_CPPFLAGS)
BUILD_COMPILER_VERSION_CFLAGS(MG_CFLAGS, MG_DEBUG_CFLAGS)
BUILD_LDFLAGS(MG_LDFLAGS)


#################################################
#						#
# SECTION 11: Check for library functions	#
#						#
#################################################

AC_MSG_NOTICE(checking for GNU compatible library functions)

AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS(memset strerror)


#################################################
#						#
# SECTION 14: Additional checks & variables	#
#						#
#################################################

AC_MSG_NOTICE(processing additional checks and variables)

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
AC_SUBST([edit], ["sed \
		-e 's|@docbaseloc[@]|\$(docbaseloc)|g' \
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
AC_SUBST(tmpheaders)

for entry in `dirname $0`/src/prg/c/inc-tmp/*.h
do
	if test -f "$entry" ;then
		tmpheaders=$tmpheaders" "$(basename "$entry")
	fi
done

#
# This creates an AutoConf substitution variable for temporary libraries.
# Temporary libraries are development copies of libraries from other packages
# which are being tested / modified in conjunction with this package.
# This variable can be consumed in the AutoMake XXX_LDADD line.
# The use of `dirname $0` to get the configure invocation directory is critical
# for parallel builds and make distcheck as the relative path always stays the
# same but configure may be invoked from different directories.
#
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

# Check a source file to ensure no command line --srcdir typo.
AC_CONFIG_SRCDIR(src/prg/c/src/libmgec/version.c)


#########################################
#					#
# SECTION 15: Specify the output files	#
#					#
#########################################

AC_MSG_NOTICE(processing output files)

#
# Non-Makefile files to generate.
# AC_CONFIG_FILES should not be used to substitute AutoConf Installation
# Directory Variables, (bindir and friends), except in Makefiles and pkg-config
# files. See GNU AutoConf manual section 4.8.2 Installation Directory Variables.
#
AC_CONFIG_FILES(doc/doxygen/Doxyfile)
AC_CONFIG_FILES(src/prg/c/pkg-config/libmgec.pc)

# Causes AC_OUTPUT to create a c preprocessor file with #define statements about
# the configuration.
AC_CONFIG_HEADERS(src/prg/c/gen/inc/config.h)

# Project Makefiles to create.
AC_CONFIG_FILES(Makefile
		doc/doxygen/Makefile
		src/man/3/listsandsorts/bstree/Makefile
		src/man/3/buf-msg/Makefile
		src/man/3/listsandsorts/dllist/Makefile
		src/man/3/errno/Makefile
		src/man/3/memory/Makefile
		src/man/3/listsandsorts/sllist/Makefile
		src/prg/c/gen/lib/Makefile
		src/prg/c/inc/Makefile
		src/prg/c/inc-tmp/Makefile
		src/prg/c/lib-tmp/Makefile
		src/prg/c/pkg-config/Makefile
		src/prg/c/src/libmgec/Makefile
		src/prg/c/src/test-bstree/Makefile
		src/prg/c/src/test-buf-msg/Makefile
		src/prg/c/src/test-dllist/Makefile
		src/prg/c/src/test-errno/Makefile
		src/prg/c/src/test-sllist/Makefile
		src/prg/c/src/run-tests/Makefile)

AC_OUTPUT

