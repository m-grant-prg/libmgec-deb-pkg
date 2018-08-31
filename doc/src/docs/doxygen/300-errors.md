Errors
======
[TOC]

\section errormsgs Messages

Error message numbers are \#defined in the [mge-errno.h](@ref mge-errno.h)
header file. The error number is used as the array element in the
[errno_desc](@ref errno_desc) array.

\section errorusage Usage

On error [mge_errno](@ref mge_errno) should be set to a value from the [header file](@ref mge-errno.h). If it is set to MGE_ERRNO or MGE_GAI then [sav_errno](@ref sav_errno) is set to errno or the getaddrinfo error code respectively.

\section errorfunctions Helper Functions

\subsection mgestrerror mge_strerror()
The [mge_strerror](@ref mge_strerror) function returns a string describing the error number given in the supplied parameter. If the error number is MGE_ERRNO or MGE_GAI then it uses the value held in [sav_errno](@ref sav_errno) to retrieve the relevant errno message or getaddrinfo error message.
