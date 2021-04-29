SRCS = unexpand.c
OBJS = $(SRCS:.c=.o)

all: unexpand

unexpand: $(OBJS)
	$(CC) $(CFLAGS) -D_XOPEN_SOURCE -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -D_XOPEN_SOURCE -c -o $@ $<

install:
	install -D -m 0755 unexpand $(DESTDIR)$(BINDIR)/unexpand
	mkdir -p $(DESTDIR)$(MANDIR)/man1
	echo '.so man1/expand.1' > $(DESTDIR)$(MANDIR)/man1/unexpand.1

clean:
	-rm -f $(OBJS) unexpand

.PHONY: install clean

include $(shell pwd)/../../config.mk
