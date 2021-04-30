SRCS = rmdir.c
OBJS = $(SRCS:.c=.o)

all: rmdir

rmdir: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 rmdir $(DESTDIR)$(BINDIR)/rmdir
	install -D -m 0644 rmdir.1 $(DESTDIR)$(MANDIR)/man1/rmdir.1

clean:
	-rm -f $(OBJS) rmdir

.PHONY: install clean

include $(shell pwd)/../../config.mk
