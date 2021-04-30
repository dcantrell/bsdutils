SRCS = mknod.c
OBJS = $(SRCS:.c=.o)

all: mknod

mknod: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 mknod $(DESTDIR)$(SBINDIR)/mknod
	install -D -m 0644 mknod.1 $(DESTDIR)$(MANDIR)/man1/mknod.1

clean:
	-rm -f $(OBJS) mknod

.PHONY: install clean

include $(shell pwd)/../../config.mk
