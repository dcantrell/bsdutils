SRCS = expand.c
OBJS = $(SRCS:.c=.o)

all: expand

expand: $(OBJS)
	$(CC) $(CFLAGS) -D_XOPEN_SOURCE -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -D_XOPEN_SOURCE -c -o $@ $<

install:
	install -D -m 0755 expand $(DESTDIR)$(BINDIR)/expand
	install -D -m 0644 expand.1 $(DESTDIR)$(MANDIR)/man1/expand.1

clean:
	-rm -f $(OBJS) expand

.PHONY: install clean

include $(shell pwd)/../../config.mk
