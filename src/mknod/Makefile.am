bin_PROGRAMS = mknod
dist_man_MANS = mknod.8 mkfifo.1

mknod_SOURCES = mknod.c
mknod_CFLAGS = -I$(top_srcdir)/compat
mknod_LDADD = $(top_builddir)/compat/libcompat.la

install-data-local:
	ln -s mknod $(DESTDIR)$(bindir)/mkfifo
