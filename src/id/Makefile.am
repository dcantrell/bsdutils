bin_PROGRAMS = id
man_MANS = id.1 groups.1 whoami.1

id_SOURCES = id.c

install-exec-local:
	ln -s id $(DESTDIR)$(bindir)/groups
	ln -s id $(DESTDIR)$(bindir)/whoami
