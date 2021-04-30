SRCS = uniq.c
OBJS = $(SRCS:.c=.o)

all: uniq

uniq: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 uniq $(DESTDIR)$(BINDIR)/uniq
	install -D -m 0644 uniq.1 $(DESTDIR)$(MANDIR)/man1/uniq.1

clean:
	-rm -f $(OBJS) uniq

.PHONY: install clean

include $(shell pwd)/../../config.mk
