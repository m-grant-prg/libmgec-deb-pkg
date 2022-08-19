#########################################################################
#									#
# Script ID: src/prg/c/inc/Makefile.am					#
# Author: Copyright (C) 2015-2022  Mark Grant				#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0-only					#
#									#
# Purpose:								#
#	AutoMake script file to generate libmgec-dev headers from	#
# source.								#
#									#
#########################################################################

#########################################################################
#									#
# Changelog								#
#									#
# Date		Author	Version	Description				#
#									#
# 12/07/2015	MG	1.0.1	First release.				#
# 06/08/2015	MG	1.0.2	Add listsandsorts.h and libmgec.h	#
# 25/10/2015	MG	1.0.3	Restructure and change to conform to	#
#				AutoTools General Template v1.0.6.	#
# 05/11/2015	MG	1.0.4	Extract bstree.h from listsandsorts.h	#
#				leaving listsandsorts.h as an umbrella.	#
# 03/05/2016	MG	1.0.5	Add single linked lists include file.	#
# 06/05/2016	MG	1.0.6	Add double linked lists include file.	#
# 15/11/2016	MG	1.0.7	Add buffer, memory and message headers.	#
# 24/01/2017	MG	1.0.8	Changes for new mge-errno handling.	#
# 22/12/2017	MG	1.0.9	Add SPDX license tags to source files.	#
# 02/01/2018	MG	1.0.10	Move to new source directory structure.	#
# 09/05/2019	MG	1.0.11	Remove shebang.				#
#				Merge dev sub-project.			#
# 29/06/2020	MG	1.0.12	Rename mge-general.h to mge-internal.h	#
# 03/12/2021	MG	1.0.13	Tighten SPDX tag.			#
# 09/06/2022	MG	1.0.14	Remove now empty mge-internal.h		#
# 19/08/2022	MG	1.0.15	Rename of portability.h			#
#				Rename of bstree.h			#
#				Rename of mgebuffer.h			#
#				Rename mgememory.h			#
#				Rename mgemessage.h			#
#				Install in package specific include	#
#				directory.				#
#									#
#########################################################################

pkginclude_HEADERS = mge-portability.h
pkginclude_HEADERS += mge-bstree.h sllist.h dllist.h
pkginclude_HEADERS += mge-buffer.h mge-errno.h mge-memory.h mge-message.h
pkginclude_HEADERS += libmgec.h

