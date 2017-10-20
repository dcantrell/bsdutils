bin_PROGRAMS = pr
man_MANS = pr.1

pr_SOURCES = pr.c egetopt.c
pr_CFLAGS = -D_GNU_SOURCE -I$(top_srcdir)/compat
pr_LDADD = $(top_builddir)/compat/libcompat.la
