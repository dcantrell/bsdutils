bin_PROGRAMS = chmod
man_MANS = chmod.1 chgrp.1 chown.8

chmod_SOURCES = chmod.c
chmod_CFLAGS = -I$(top_srcdir)/compat
chmod_LDADD = $(top_builddir)/compat/libcompat.la

install-exec-local:
	ln -sf chmod $(DESTDIR)$(bindir)/chgrp
	mkdir -p $(DESTDIR)$(sbindir)
	ln -sf chmod $(DESTDIR)$(sbindir)/chown
