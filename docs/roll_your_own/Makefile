#  -= MPMS =-     Makefile Project Management Structure++++
#  Name        :    Vijay Ramesh
#  Date        :    Thu Apr 12 04:27:18 CDT 2007
#  FileName    :    Makefile
#
#  License     :    ISC Licence
#
#                   Copyright (c) 2007, Vijay Ramesh <vramesh2@uiuc.edu>
#
#                   Permission to use, copy, modify, and distribute this software for any
#                   purpose with or without fee is hereby granted, provided that the above
#                   copyright notice and this permission notice appear in all copies.
#
#                   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
#                   WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
#                   MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
#                   ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
#                   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
#                   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
#                   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#
#  Project     :    The MPMS is a Makefile structure for easily managing
#                   projects. This is supposed to resemble and work much
#                   like the BSD make system they use for ports. However,
#                   all syntax is written in gmake syntax for portability.
#                   The idea is completely from BSD and all the credit goes
#                   to them. I just liked the idea and found it useful to
#                   manage projects.
#
#  Purpose     :    Makefile is the normal file you would write for
#                   directories to tell make which subdirectories this directory
#                   is dependant on. Depends on subdir.mk and variables.mk. This
#                   file is independant and can run by itself.
#----
#  User Settings++++
#  Name of the current directory for identification
NAME = "currdir"

#  List of subdirectories
SUBDIR +=

#----
#  Variable Definitions++++
include ~/.mpms/variables.mk
#----
#  Subdirectory include++++
include ~/.mpms/subdir.mk
#----
