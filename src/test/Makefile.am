bin_PROGRAMS = test
man_MANS = test.1

test_SOURCES = test.c
test_CFLAGS = -I$(top_srcdir)/compat
test_LDADD = $(top_builddir)/compat/libcompat.la

install-data-local:
	ln -s test $(DESTDIR)$(bindir)/[
