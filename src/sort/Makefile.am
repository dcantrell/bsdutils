bin_PROGRAMS = sort
dist_man_MANS = sort.1

sort_SOURCES = bwstring.c coll.c file.c mem.c radixsort.c sort.c vsort.c
sort_CFLAGS = -I$(top_srcdir)/compat $(OPENSSL_CFLAGS) -D_GNU_SOURCE
sort_LDADD = $(top_builddir)/compat/libcompat.la $(OPENSSL_LIBS)

EXTRA_DIST = bwstring.h coll.h file.h mem.h radixsort.h sort.h vsort.h
