SRCS = chmod.c
OBJS = $(SRCS:.c=.o)

all: chmod

chmod: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 chmod $(DESTDIR)$(BINDIR)/chmod
	install -D -m 0644 chmod.1 $(DESTDIR)$(MANDIR)/man1/chmod.1

clean:
	-rm -f $(OBJS) chmod

.PHONY: install clean

include $(shell pwd)/../../config.mk
