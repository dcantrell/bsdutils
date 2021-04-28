CC = gcc

# Standard compiler flags
CFLAGS = -Wall -O2 -g

# We need local header files
#CFLAGS += -I$(shell pwd)/include

# Where to install things
DESTDIR ?=
BINDIR  ?= /usr/bin
MANDIR  ?= /usr/share/man
