bin_PROGRAMS = stty
dist_man_MANS = stty.1

stty_SOURCES = cchar.c gfmt.c key.c modes.c print.c stty.c
stty_CFLAGS = -I$(top_srcdir)/compat
stty_LDADD = $(top_builddir)/compat/libcompat.la

EXTRA_DIST = extern.h stty.h
