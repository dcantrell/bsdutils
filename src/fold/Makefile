SRCS = fold.c
OBJS = $(SRCS:.c=.o)

all: fold

fold: $(OBJS)
	$(CC) $(CFLAGS) -D_XOPEN_SOURCE -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -D_XOPEN_SOURCE -c -o $@ $<

install:
	install -D -m 0755 fold $(DESTDIR)$(BINDIR)/fold
	install -D -m 0644 fold.1 $(DESTDIR)$(MANDIR)/man1/fold.1

clean:
	-rm -f $(OBJS) fold

.PHONY: install clean

include $(shell pwd)/../../config.mk
