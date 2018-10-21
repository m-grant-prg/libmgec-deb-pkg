#! /usr/bin/env bash
#########################################################################
#									#
# Script ID: ./Makefile.am						#
# Author: Copyright (C) 2017-2018  Mark Grant				#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0					#
#									#
# Purpose:								#
#	AutoMake script file to generate libmgec all projects from	#
# source.								#
#									#
#########################################################################

#########################################################################
#									#
# Changelog								#
#									#
# Date		Author	Version	Description				#
#									#
# 21/12/2017	MG	1.0.1	First release.				#
# 02/01/2018	MG	1.0.2	Move to new source directory structure.	#
# 08/06/2018	MG	1.0.3	Add srctarball target to build a source	#
#				tarball in the build directory. Uses	#
#				git archive to archive HEAD.		#
# 20/06/2018	MG	1.0.4	Simplify as per it's use.		#
# 21/10/2018	MG	1.0.5	Change srctarball target to build with	#
#				src between package name and version in	#
#				filename.				#
#									#
#########################################################################

SUBDIRS = dev lib doc


srctarball:
	@cwd="$${PWD}" && \
	targ="$${cwd}/@PACKAGE_TARNAME@-src-@PACKAGE_VERSION@.tar.gz" && \
	cd @srcdir@ && \
	echo "making srctarball from @srcdir@" && \
	echo "GA	$${targ}" && \
	git archive --format=tar.gz \
		--prefix=@PACKAGE_TARNAME@-@PACKAGE_VERSION@/ \
		--output=$${targ} \
		HEAD && \
	cd -

