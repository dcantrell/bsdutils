bin_PROGRAMS = sort
man_MANS = sort.1

sort_SOURCES = bwstring.c coll.c file.c mem.c radixsort.c sort.c vsort.c
sort_CFLAGS = -I$(top_srcdir)/compat $(OPENSSL_CFLAGS)
sort_LDADD = $(top_builddir)/compat/libcompat.la $(OPENSSL_LIBS)
