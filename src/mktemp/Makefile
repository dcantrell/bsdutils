SRCS = mktemp.c
OBJS = $(SRCS:.c=.o)

all: mktemp

mktemp: $(OBJS)
	$(CC) $(CFLAGS) -D_GNU_SOURCE -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -D_GNU_SOURCE -c -o $@ $<

install:
	install -D -m 0755 mktemp $(DESTDIR)$(BINDIR)/mktemp
	install -D -m 0644 mktemp.1 $(DESTDIR)$(MANDIR)/man1/mktemp.1

clean:
	-rm -f $(OBJS) mktemp

.PHONY: install clean

include $(shell pwd)/../../config.mk
