SRCS = nice.c
OBJS = $(SRCS:.c=.o)

all: nice

nice: $(OBJS)
	$(CC) $(CFLAGS) -D_GNU_SOURCE -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -D_GNU_SOURCE -c -o $@ $<

install:
	install -D -m 0755 nice $(DESTDIR)$(BINDIR)/nice
	install -D -m 0644 nice.1 $(DESTDIR)$(MANDIR)/man1/nice.1

clean:
	-rm -f $(OBJS) nice

.PHONY: install clean

include $(shell pwd)/../../config.mk
