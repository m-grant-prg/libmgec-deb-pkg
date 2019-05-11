#########################################################################
#									#
# Script ID: src/prg/c/inc/Makefile.am					#
# Author: Copyright (C) 2015-2019  Mark Grant				#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0					#
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
#									#
#########################################################################

include_HEADERS = portability.h
include_HEADERS += bstree.h sllist.h dllist.h
include_HEADERS += mgebuffer.h mge-errno.h mgememory.h mgemessage.h
include_HEADERS += libmgec.h

noinst_HEADERS = mge-general.h

