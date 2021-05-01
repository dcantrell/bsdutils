SRCS = test.c
OBJS = $(SRCS:.c=.o)

all: test

test: $(OBJS)
	$(CC) $(CFLAGS) -D_GNU_SOURCE -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -D_GNU_SOURCE -c -o $@ $<

install:
	install -D -m 0755 test $(DESTDIR)$(BINDIR)/test
	install -D -m 0644 test.1 $(DESTDIR)$(MANDIR)/man1/test.1

clean:
	-rm -f $(OBJS) test

.PHONY: install clean

include $(shell pwd)/../../config.mk
