SRCS = chroot.c
OBJS = $(SRCS:.c=.o)

all: chroot

chroot: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 chroot $(DESTDIR)$(SBINDIR)/chroot
	install -D -m 0644 chroot.1 $(DESTDIR)$(MANDIR)/man8/chroot.8

clean:
	-rm -f $(OBJS) chroot

.PHONY: install clean

include $(shell pwd)/../../config.mk
