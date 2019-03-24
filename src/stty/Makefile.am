bin_PROGRAMS = stty
man_MANS = stty.1

stty_SOURCES = cchar.c gfmt.c key.c modes.c print.c stty.c
stty_CFLAGS = -I$(top_srcdir)/compat
stty_LDADD = $(top_builddir)/compat/libcompat.la
