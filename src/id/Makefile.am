bin_PROGRAMS = id
dist_man_MANS = id.1 groups.1 whoami.1

id_SOURCES = id.c
id_CFLAGS = -I$(top_srcdir)/compat
id_LDADD = $(top_builddir)/compat/libcompat.la

install-exec-local:
	ln -s id $(DESTDIR)$(bindir)/groups
	ln -s id $(DESTDIR)$(bindir)/whoami
