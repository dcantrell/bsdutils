CC = gcc

# Standard compiler flags
CFLAGS = -Wall -O2 -g

# Define some macros to eliminate some FreeBSD-specifics in the code
CFLAGS += -Dlint
CFLAGS += -D'__FBSDID(x)='
CFLAGS += -D__dead2=
CFLAGS += -D__unused=

# Where to install things
DESTDIR ?=
BINDIR  ?= /usr/bin
SBINDIR ?= /usr/sbin
MANDIR  ?= /usr/share/man
