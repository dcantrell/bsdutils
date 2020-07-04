bin_PROGRAMS = pr
dist_man_MANS = pr.1

pr_SOURCES = pr.c egetopt.c
pr_CFLAGS = -I$(top_srcdir)/compat -D_GNU_SOURCE
pr_LDADD = $(top_builddir)/compat/libcompat.la

EXTRA_DIST = extern.h pr.h
