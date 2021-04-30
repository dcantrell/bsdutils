SRCS = head.c
OBJS = $(SRCS:.c=.o)

all: head

head: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 head $(DESTDIR)$(BINDIR)/head
	install -D -m 0644 head.1 $(DESTDIR)$(MANDIR)/man1/head.1

clean:
	-rm -f $(OBJS) head

.PHONY: install clean

include $(shell pwd)/../../config.mk
