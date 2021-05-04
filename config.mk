CC        = gcc
CXX       = g++

# Standard compiler flags
CFLAGS    = -Wall -O2 -g

# Define some macros to eliminate some FreeBSD-specifics in the code
CFLAGS   += -Dlint
CFLAGS   += -D'__FBSDID(x)='
CFLAGS   += -D__dead2=
CFLAGS   += -D__unused=
CFLAGS   += -D'__printf0like(x, y)='
CFLAGS   += -D'__SCCSID(x)='

# Use the C flags for C++ code
CXXFLAGS  = $(CFLAGS)

# Where to install things
DESTDIR  ?=
BINDIR   ?= /usr/bin
SBINDIR  ?= /usr/sbin
MANDIR   ?= /usr/share/man
