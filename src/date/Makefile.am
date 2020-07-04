bin_PROGRAMS = date
dist_man_MANS = date.1

date_SOURCES = date.c
date_CFLAGS = -I$(top_srcdir)/compat -D_DEFAULT_SOURCE -D_XOPEN_SOURCE
date_LDADD = $(top_builddir)/compat/libcompat.la -lutil
