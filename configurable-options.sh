#! /usr/bin/env bash

#########################################################################
#									#
# Script ID: configurable-options.sh					#
# Author: Copyright (C) 2021  Mark Grant				#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0					#
#									#
# Purpose:								#
# To provide a menu system to allow overrides of some default values	#
# such as DEF_BUF_SIZE.							#
#									#
# Syntax:	configurable-options.sh					#
#									#
# Exit codes used:-							#
# Bash standard Exit Codes:	0 - success				#
#				1 - general failure			#
# User-defined exit code range is 64 - 113				#
#	C/C++ Semi-standard exit codes from sysexits.h range is 64 - 78	#
#		EX_USAGE	64	command line usage error	#
#		EX_DATAERR	65	data format error		#
#		EX_NOINPUT	66	cannot open input		#
#		EX_NOUSER	67	addressee unknown		#
#		EX_NOHOST	68	host name unknown		#
#		EX_UNAVAILABLE	69	service unavailable		#
#		EX_SOFTWARE	70	internal software error		#
#		EX_OSERR	71	system error (e.g., can't fork)	#
#		EX_OSFILE	72	critical OS file missing	#
#		EX_CANTCREAT	73	can't create (user) output file	#
#		EX_IOERR	74	input/output error		#
#		EX_TEMPFAIL	75	temp failure; user is invited	#
#					to retry			#
#		EX_PROTOCOL	76	remote error in protocol	#
#		EX_NOPERM	77	permission denied		#
#		EX_CONFIG	78	configuration error		#
#	User-defined (here) exit codes range 79 - 113:			#
#		None							#
#									#
# Further Info:								#
#									#
#########################################################################

#########################################################################
#									#
# Changelog								#
#									#
# Date		Author	Version	Description				#
#									#
# 15/04/2021	MG	1.0.1	Created.				#
#									#
#########################################################################


##################
# Init variables #
##################

readonly version=1.0.1			# set version variable


#############
# Functions #
#############

# Standard trap exit function.
# No parameters.
# No return value.
trap_exit()
{
	local -i exit_code=$?
	local msg

	msg="Script terminating with exit code $exit_code due to trap received."
	output "$msg" 1
	script_exit $exit_code
}

# Setup trap
trap trap_exit SIGHUP SIGINT SIGQUIT SIGTERM

# Process Default Buffer Size
# No parameters
# No return value
proc_def_buf_size()
{
	local status

	while [[ $status != 0 ]]; do
		DEF_BUF_SIZE=$(whiptail --title "Configurable Options" \
			--inputbox "Default Buffer Size (in bytes) between 256 and 10240000" 10 60 256 3>&1 1>&2 2>&3)
		status=$?

		if [[ $status != 0 ]]; then
			exit $status
		fi

		if [[ ! ($DEF_BUF_SIZE =~ ^[0-9]*$) ]]; then
			status=1
			whiptail --title "Error Message" --msgbox \
				"Buffer Size must be numeric" 10 60
		elif (( $DEF_BUF_SIZE < 256 || $DEF_BUF_SIZE > 10485760 )); then
			whiptail --title "Error Message" --msgbox \
				"Invalid Buffer Size, must be between 256B and 10485760B" 10 60
			status=1
		fi
	done
	ret_string=" CLA_DEF_CPP_VALUES=\" -DDEF_BUF_SIZE=$DEF_BUF_SIZE"
}

# Process Default Buffer Unused Default Size Multiplier
# No parameters
# No return value
proc_buf_unused_def_size_mult()
{
	local status

	while [[ $status != 0 ]]; do
		BUF_UNUSED_DEF_SIZE_MULT=$(whiptail --title \
			"Configurable Options" \
			--inputbox "Buffer Unused Default Size Multiplier between 2 and 10" 10 60 3 3>&1 1>&2 2>&3)
		status=$?

		if [[ $status != 0 ]]; then
			exit $status
		fi

		if [[ ! ($BUF_UNUSED_DEF_SIZE_MULT =~ ^[0-9]*$) ]]; then
			status=1
			whiptail --title "Error Message" --msgbox \
				"Unused Buffer Size Multiplier must be numeric"\
				10 60
		elif (( $BUF_UNUSED_DEF_SIZE_MULT < 2 \
			|| $BUF_UNUSED_DEF_SIZE_MULT > 10 )); then
			whiptail --title "Error Message" --msgbox \
				"Invalid Buffer Unused Size Multiplier, must be 2 <= size <= 10" 10 60
			status=1
		fi
	done
	ret_string+=" -DBUF_UNUSED_DEF_SIZE_MULT=$BUF_UNUSED_DEF_SIZE_MULT"
}

# Process Buffer Maximum Unreachable Percentage
# No parameters
# No return value
proc_buf_max_unreach_percent()
{
	local status

	while [[ $status != 0 ]]; do
		BUF_MAX_UNREACH_PERCENT=$(whiptail --title \
			"Configurable Options" \
			--inputbox "Buffer Maximum Unreachable Percentage between 20 and 50" 10 60 33 3>&1 1>&2 2>&3)
		status=$?

		if [[ $status != 0 ]]; then
			exit $status
		fi

		if [[ ! ($BUF_MAX_UNREACH_PERCENT =~ ^[0-9]*$) ]]; then
			status=1
			whiptail --title "Error Message" --msgbox \
				"Unreachable Percentage must be numeric" 10 60
		elif (( $BUF_MAX_UNREACH_PERCENT < 20 \
			|| $BUF_MAX_UNREACH_PERCENT > 50 )); then
			whiptail --title "Error Message" --msgbox \
				"Invalid Unreachable Percentage, must be 20 <= size <= 50" 10 60
			status=1
		fi
	done
	ret_string+=" -DBUF_MAX_UNREACH_PERCENT=$BUF_MAX_UNREACH_PERCENT"
}

# Process Default Message Size
# No parameters
# No return value
proc_def_msg_size()
{
	local status

	while [[ $status != 0 ]]; do
		DEF_MSG_SIZE=$(whiptail --title "Configurable Options" \
			--inputbox "Default Message Size (in bytes) between 256 and 10240000" 10 60 256 3>&1 1>&2 2>&3)
		status=$?

		if [[ $status != 0 ]]; then
			exit $status
		fi

		if [[ ! ($DEF_MSG_SIZE =~ ^[0-9]*$) ]]; then
			status=1
			whiptail --title "Error Message" --msgbox \
				"Message Size must be numeric" 10 60
		elif (( $DEF_MSG_SIZE < 256 || $DEF_MSG_SIZE > 10485760 )); then
			whiptail --title "Error Message" --msgbox \
				"Invalid Message Size, must be between 256B and 10485760B" 10 60
			status=1
		fi
	done
	ret_string+=" -DDEF_MSG_SIZE=$DEF_MSG_SIZE"
}


########
# Main #
########

proc_def_buf_size

proc_buf_unused_def_size_mult

proc_buf_max_unreach_percent

proc_def_msg_size

# Print the configure CLA to stdout
ret_string+="\""
echo " $ret_string"

exit 0

