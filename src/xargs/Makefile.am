bin_PROGRAMS = xargs
dist_man_MANS = xargs.1

xargs_SOURCES = xargs.c strnsubst.c
xargs_CFLAGS = -I$(top_srcdir)/compat
xargs_LDADD = $(top_builddir)/compat/libcompat.la

EXTRA_DIST = pathnames.h
