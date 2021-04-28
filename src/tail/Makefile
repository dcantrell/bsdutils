SRCS = forward.c misc.c read.c reverse.c tail.1 tail.c
OBJS = $(SRCS:.c=.o)

all: tail

tail: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 tail $(DESTDIR)$(BINDIR)/tail
	install -D -m 0644 tail.1 $(DESTDIR)$(MANDIR)/man1/tail.1

clean:
	-rm -f $(OBJS) tail

.PHONY: install clean

include $(shell pwd)/../../config.mk
