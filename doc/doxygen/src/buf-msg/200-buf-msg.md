Message Buffers and Messages
============================
\tableofcontents

\section overview Overview

These library functions address the need to exchange meassages, maybe between
processes on the same machine, or, maybe between machines using UDP or TCP
streams. The only fixed aspect of a message is that it contains 1 or more fields
separated by a 'separator' charcter and terminated by a 'terminator' character.
These 2 characters are defined in the [mgemessage struct](@ref mgemessage).

The data source for this system is a flat buffer which may contain part of a
message, a complete message or mutiple messages.

This flat buffer is first loaded into a [mgebuffer struct](@ref mgebuffer) which
maintains a buffer and indexes to the next byte to be processed and the next
free byte.

This [mgebuffer struct](@ref mgebuffer) is then processed, extracting data into
a [mgemessage struct](@ref mgemessage) until it contains a complete message.
When it contains a complete message it is parsed into individual arguments held
in the struct.

@diafile buf-msg.dia



\section buf Buffers

The buffers area consists of 2 functions; concat_buf() and trim_buf().

\subsection concatbuf concat_buf()
concat_buf() takes the supplied flat buffer and appends it to the buffer in the
supplied [mgebuffer struct](@ref mgebuffer) updating the relevant pointers.

\subsection trimbuf trim_buf()
The trim_buf() function removes processed data from the
[mgebuffer struct](@ref mgebuffer) buffer. It is typically called after some or
all of the data in the [mgebuffer struct](@ref mgebuffer) has been
processed@cond INTERNAL, often after get_msg() has extracted data to a [mgemessage struct](@ref mgemessage)@endcond.


\section messages Messages

The message area API consists of 2 functions; pull_msg() and clear_msg(). @cond INTERNAL
Behind the scenes get_msg() and deconstruct_msg() are called from pull_msg().
@endcond

The following diagram shows a typical message workflow.

@diafile msg-flow.dia


\subsection msgfunctions Functions
\subsubsection pullmsg pull_msg()
The pull_msg() function extracts data from the
[mgebuffer struct](@ref mgebuffer) buffer and loads it into a
[mgemessage struct](@ref mgemessage). The processed part of the
[mgebuffer struct](@ref mgebuffer) buffer is then removed by invoking
trim_buf(). If the [mgemessage struct](@ref mgemessage) buffer then holds a
complete message it @cond INTERNAL
is deconstructed and@endcond fully populates the [mgemessage struct](@ref mgemessage).

@diafile pull-msg-flow.dia

@cond INTERNAL
The same diagram with function names.

@diafile pull-msg-flow-int.dia


\subsubsection getmsg get_msg()
The get_msg() function extracts data, (partial or complete messages), from the
[mgebuffer struct](@ref mgebuffer) buffer and loads them into a
[mgemessage struct](@ref mgemessage).
@diafile get-msg-flow.dia


\subsubsection deconstructmsg deconstruct_msg()
The deconstruct_msg() function is invoked by the pull_msg() function when the
[mgemessage struct](@ref mgemessage) buffer contains a complete message. This
function then parses the message into it's individual fields and places them in
argv updating argc. (argc and argv have the same function and format as in the
standard C main function).

@endcond

\subsubsection clearmsg clear_msg()
The clear_msg() function frees the message buffer and argument storage and
resets the other fileds to initial values.
