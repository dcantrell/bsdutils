bin_PROGRAMS = mknod
man_MANS = mknod.8 mkfifo.1

mknod_SOURCES = mknod.c

install-data-local:
	ln -s mknod $(DESTDIR)$(bindir)/mkfifo
