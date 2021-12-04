#! /usr/bin/env bash

#########################################################################
#									#
# Script ID: configurable-options.sh					#
# Author: Copyright (C) 2021  Mark Grant				#
#									#
# Released under the GPLv3 only.					#
# SPDX-License-Identifier: GPL-3.0-only					#
#									#
# Purpose:								#
# It make sense in many code-bases to allow the override of some	#
# constants which in certain circumstances may benefit from a different	#
# value. This script allows such overrides to be passed to the		#
# AutoTools system and used in the compile commands. The modified	#
# values are presented as a string of -DConstant=value constructs.	#
#									#
# Syntax:	configurable-options.sh <File or named pipe>		#
#		Without the optional file, output is to stdout.		#
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
# 31/05/2021	MG	1.0.2	Re-write to improve and to use Dialog.	#
# 03/12/2021	MG	1.0.3	Tighten SPDX tag.			#
#									#
#########################################################################


##################
# Init variables #
##################

readonly version=1.0.3			# set version variable

output_target=$1			# Filename for the results

# Set default values
DEF_BUF_SIZE=256
BUF_UNUSED_DEF_SIZE_MULT=3
BUF_MAX_UNREACH_PERCENT=33
DEF_MSG_SIZE=256

# Define the dialog exit status codes
: ${DIALOG_OK=0}
: ${DIALOG_CANCEL=1}
: ${DIALOG_EXIT=1}
: ${DIALOG_HELP=2}
: ${DIALOG_ESC=255}


#############
# Functions #
#############

# Standard function to emit messages depending on various parameters.
# Parameters -	$1 What:-	The message to emit.
#		$2 Where:-	stdout == 0
#				stderr == 1
# No return value.
output()
{
	if (( !$2 )); then
		printf "%s\n" "$1"
	else
		printf "%s\n" "$1" 1>&2
	fi
}

# Standard function to tidy up and return exit code.
# Parameters - 	$1 is the exit code.
# No return value.
script_exit()
{
	exit $1
}

# Standard function to test command error and exit if non-zero.
# Parameters - 	$1 is the exit code, (normally $? from the preceding command).
# No return value.
std_cmd_err_handler()
{
	if (( $1 )); then
		script_exit $1
	fi
}

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

# Check dialog is available
# No parameters
# Returns zero on success 69 on failure
dialog_reqd()
{
	which dialog > /dev/null
	if (( $? )); then
		printf "%s\n" "Please install dialog first." 1>&2
		return 69
	fi
	return 0
}

# Validate Default Buffer Size
# %1 is the value to check
# Returns 0 if valid, 1 if invalid
validate_def_buf_size()
{
	declare -i status=0

	if [[ ! ($1 =~ ^[0-9]*$) ]]; then
		status=1
		dialog --backtitle "Compile-time Values" \
			--title "Error Message" --msgbox \
			"Buffer Size must be numeric" 10 60
	elif (( $1 < 256 || $1 > 10485760 )); then
		dialog --backtitle "Compile-time Values" \
			--title "Error Message" --msgbox \
			"Invalid Buffer Size, must be between 256 Bytes and 10485760 Bytes" 10 60
		status=1
	fi
	if (( $status == 0 )); then
		DEF_BUF_SIZE=$1
	fi
	return $status
}

# Validate Buffer Unused Default Size Multiplier
# %1 is the value to check
# Returns 0 if valid, 1 if invalid
validate_buf_unused_def_size_mult()
{
	declare -i status=0

	if [[ ! ($1 =~ ^[0-9]*$) ]]; then
		status=1
		dialog --backtitle "Compile-time Values" \
			--title "Error Message" \
			--msgbox \
			"Buffer Unused Default Size Multiplier must be numeric"\
			10 60
	elif (( $1 < 2 || $1 > 10 )); then
		dialog --backtitle "Compile-time Values" \
			--title "Error Message" \
			--msgbox \
			"Invalid Buffer Unused Default Size Multiplier, must be between 2 and 10" 10 60
		status=1
	fi
	if (( $status == 0 )); then
		BUF_UNUSED_DEF_SIZE_MULT=$1
	fi
	return $status
}

# Validate Buffer Max Unreachable Percentage
# %1 is the value to check
# Returns 0 if valid, 1 if invalid
validate_buf_max_unreach_percent()
{
	declare -i status=0

	if [[ ! ($1 =~ ^[0-9]*$) ]]; then
		status=1
		dialog --backtitle "Compile-time Values" \
			--title "Error Message" \
			--msgbox \
			"Buffer Max Unreachable Percentage must be numeric" \
			10 60
	elif (( $1 < 20 || $1 > 50 )); then
		dialog --backtitle "Compile-time Values" \
			--title "Error Message" \
			--msgbox \
			"Invalid Buffer Max Unreachable Percentage, must be between 20 and 50" 10 60
		status=1
	fi
	if (( $status == 0 )); then
		BUF_MAX_UNREACH_PERCENT=$1
	fi
	return $status
}

# Process Buffer values
# No parameters
# No return value
proc_buffer()
{
	local form_help_txt="The answers entered here must be numeric and lie between the minimum and maximum values specified in the individual prompts."
	local form_txt="You can use the UP/DOWN arrow keys to select a value.\nOK retains the values displayed and returns up the menu hierarchy.\nCancel ends the input session and returns up the menu hierarchy without retaining any changed values.\nESC cancels this configuration session entirely and does not pass back any values at all.\n\nSelect The Values To Amend:"
	declare -i i=0
	local ret_string
	declare -i retval=1
	declare -i status
	local value
	local values

	while true; do
		exec 3>&1
		values=$(dialog --help-button \
		--backtitle "Compile-time Values" \
		--title "Buffer values" \
		--form "$form_txt" \
		18 65 0 \
		"Buffer Size. (256 <= X <= 10485760 Bytes)" 1 1 "$DEF_BUF_SIZE" 1 49 9 0 \
		"Unused buffer size multiplier. (2 <= X <= 10)" 2 1 "$BUF_UNUSED_DEF_SIZE_MULT" 2 49 3 0 \
		"Maximum unreachable percentage. (20 <= X <= 50)" 3 1 "$BUF_MAX_UNREACH_PERCENT" 3 49 3 0 \
		2>&1 1>&3)
		retval=$?
		exec 3>&-

		case $retval in
		$DIALOG_OK)
			i=0
			for value in $values; do
				if (( i == 0 )); then
					validate_def_buf_size "$value"
					status=$?
				elif (( $i == 1 )); then
					validate_buf_unused_def_size_mult \
						"$value"
					status+=$?
				elif (( $i == 2 )); then
					validate_buf_max_unreach_percent \
						"$value"
					status+=$?
				fi
				(( i++ ))
			done
			if (( $status == 0 )); then
				break
			fi
			;;
		$DIALOG_CANCEL)
			break
			;;
		$DIALOG_HELP)
			dialog --title "Main menu help" \
			--backtitle "Compile-time Values" \
			--msgbox "$form_help_txt" 10 50
			;;
		$DIALOG_ESC)
			script_exit 0
			;;
		esac
	done
}

# Validate Default Message Size
# %1 is the value to check
# Returns 0 if valid, 1 if invalid
validate_def_msg_size()
{
	declare -i status=0

	if [[ ! ($1 =~ ^[0-9]*$) ]]; then
		status=1
		dialog --backtitle "Compile-time Values" \
			--title "Error Message" --msgbox \
			"Message Size must be numeric" 10 60
	elif (( $1 < 256 || $1 > 10485760 )); then
		dialog --backtitle "Compile-time Values" \
			--title "Error Message" --msgbox \
			"Invalid Message Size, must be between 256 Bytes and 10485760 Bytes" 10 60
		status=1
	fi
	if (( $status == 0 )); then
		DEF_MSG_SIZE=$1
	fi
	return $status
}

# Process Message values
# No parameters
# No return value
proc_message()
{
	local input_help_txt="The answers entered here must be numeric and lie between the minimum and maximum values specified in the individual prompts."
	local input_txt="Please enter a value.\nOK retains the values displayed and returns up the menu hierarchy.\nCancel ends the input session and returns up the menu hierarchy without retaining any changed values.\nESC cancels this configuration session entirely and does not pass back any values at all.\n\nMessage Size. (256 <= X <= 10485760 Bytes)"
	declare -i i=0
	local ret_string
	declare -i retval=1
	declare -i status
	local value

	while true; do
		exec 3>&1
		value=$(dialog --help-button \
		--backtitle "Compile-time Values" \
		--title "Message values" \
		--inputbox "$input_txt" 15 60 "$DEF_MSG_SIZE" \
		2>&1 1>&3)
		retval=$?
		exec 3>&-

		case $retval in
		$DIALOG_OK)
			validate_def_msg_size "$value"
			status=$?
			if (( $status == 0 )); then
				break
			fi
			;;
		$DIALOG_CANCEL)
			break
			;;
		$DIALOG_HELP)
			dialog --title "Main menu help" \
			--backtitle "Compile-time Values" \
			--msgbox "$input_help_txt" 10 50
			;;
		$DIALOG_ESC)
			script_exit 0
			;;
		esac
	done
}

# Process level 0 menu
# No parameters
# No return value
proc_menu_0()
{
	local menu_help_txt="It make sense in many code-bases to allow the override of some constants which in certain circumstances may benefit from a different value. This script allows such overrides to be passed to the AutoTools system and used in the compile commands. The modified values are presented as a string of -DConstant=value constructs."
	local menu_item
	local menu_txt="You can use the UP/DOWN arrow keys or the number keys to choose an option.\nOK invokes the menu option.\nExit ends the configuration session passing back the values entered.\nESC cancels this configuration session and does not pass back any values at all.\n\nSelect The Area To Amend:"
	local ret_string
	declare -i retval=1


	while true; do
		exec 3>&1
		menu_item=$(dialog --help-button \
		--backtitle "Compile-time Values" \
		--title "Main Menu" \
		--cancel-label "Exit" \
		--menu "$menu_txt" \
		18 60 \
		2 1 Buffer 2 Message \
		2>&1 1>&3)
		retval=$?
		exec 3>&-

		case $retval in
		$DIALOG_OK)
			case $menu_item in
			1)
				proc_buffer
				;;
			2)
				proc_message
				;;
			esac
			;;
		$DIALOG_EXIT)
			break
			;;
		$DIALOG_HELP)
			dialog --title "Main menu help" \
			--backtitle "Compile-time Values" \
			--msgbox "$menu_help_txt" 10 60
			;;
		$DIALOG_ESC)
			script_exit 0
			;;
		esac
	done
	ret_string=" CLA_DEF_CPP_VALUES=\" -DDEF_BUF_SIZE=$DEF_BUF_SIZE"
	ret_string+=" -DBUF_UNUSED_DEF_SIZE_MULT=$BUF_UNUSED_DEF_SIZE_MULT"
	ret_string+=" -DBUF_MAX_UNREACH_PERCENT=$BUF_MAX_UNREACH_PERCENT"
	ret_string+=" -DDEF_MSG_SIZE=$DEF_MSG_SIZE\""
	if [[ -n  $output_target ]]; then
		printf "%s\n" "$ret_string" > $output_target
	else
		printf "%s\n" "$ret_string"
	fi
}


########
# Main #
########

dialog_reqd
std_cmd_err_handler $?

proc_menu_0
std_cmd_err_handler $?

script_exit 0

