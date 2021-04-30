SRCS = fmt.c
OBJS = $(SRCS:.c=.o)

all: fmt

fmt: $(OBJS)
	$(CC) $(CFLAGS) -D_XOPEN_SOURCE -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -D_XOPEN_SOURCE -c -o $@ $<

install:
	install -D -m 0755 fmt $(DESTDIR)$(BINDIR)/fmt
	install -D -m 0644 fmt.1 $(DESTDIR)$(MANDIR)/man1/fmt.1

clean:
	-rm -f $(OBJS) fmt

.PHONY: install clean

include $(shell pwd)/../../config.mk
