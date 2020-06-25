bin_PROGRAMS = expr
man_MANS = expr.1

expr_SOURCES = expr.c
expr_CFLAGS = -I$(top_srcdir)/compat -D_GNU_SOURCE
expr_LDADD = $(top_builddir)/compat/libcompat.la
