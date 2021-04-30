SRCS = sync.c
OBJS = $(SRCS:.c=.o)

all: sync

sync: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 sync $(DESTDIR)$(SBINDIR)/sync
	install -D -m 0644 sync.1 $(DESTDIR)$(MANDIR)/man1/sync.1

clean:
	-rm -f $(OBJS) sync

.PHONY: install clean

include $(shell pwd)/../../config.mk
