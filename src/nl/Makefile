SRCS = nl.c
OBJS = $(SRCS:.c=.o)

all: nl

nl: $(OBJS)
	$(CC) $(CFLAGS) -D_GNU_SOURCE -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -D_GNU_SOURCE -c -o $@ $<

install:
	install -D -m 0755 nl $(DESTDIR)$(BINDIR)/nl
	install -D -m 0644 nl.1 $(DESTDIR)$(MANDIR)/man1/nl.1

clean:
	-rm -f $(OBJS) nl

.PHONY: install clean

include $(shell pwd)/../../config.mk
