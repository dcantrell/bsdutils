bin_PROGRAMS = chmod
man_MANS = chmod.1 chgrp.1 chown.8 chflags.1

chmod_SOURCES = chmod.c

install-exec-local:
	ln -s chmod $(DESTDIR)$(bindir)/chgrp
	ln -s chmod $(DESTDIR)$(sbindir)/chown
	ln -s chmod $(DESTDIR)$(bindir)/chflags
