Memory
======
\tableofcontents
\section mgrealloc mg_realloc

[mg_realloc](@ref mg_realloc) is a wrapper for realloc adding error handling in
terms of setting [mge_errno](@ref mge_errno) and logging a message to syslog.

If you pass NULL to the function it behaves like realloc, that is to say it
behaves like malloc.
