SRCS = true.c
OBJS = $(SRCS:.c=.o)

all: true

basename: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 true $(DESTDIR)$(BINDIR)/true
	install -D -m 0644 true.1 $(DESTDIR)$(MANDIR)/man1/true.1

clean:
	-rm -f $(OBJS) true

.PHONY: install clean

include $(shell pwd)/../../config.mk
