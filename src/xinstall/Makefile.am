noinst_PROGRAMS = xinstall
man_MANS = install.1

xinstall_SOURCES = xinstall.c
xinstall_CFLAGS = -I$(top_srcdir)/compat
xinstall_LDADD = $(top_builddir)/compat/libcompat.la

install-exec-local:
	$(INSTALL) -m 0755 xinstall $(DESTDIR)$(bindir)/install$(EXEEXT)
