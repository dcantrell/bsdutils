bin_PROGRAMS = ls
man_MANS = ls.1

ls_SOURCES = cmp.c ls.c main.c print.c util.c utf8.c
ls_CFLAGS = -I$(top_srcdir)/compat -D_XOPEN_SOURCE=700 -D_DEFAULT_SOURCE
ls_LDADD = $(top_builddir)/compat/libcompat.la
