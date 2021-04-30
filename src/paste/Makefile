SRCS = paste.c
OBJS = $(SRCS:.c=.o)

all: paste

paste: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 paste $(DESTDIR)$(BINDIR)/paste
	install -D -m 0644 paste.1 $(DESTDIR)$(MANDIR)/man1/paste.1

clean:
	-rm -f $(OBJS) paste

.PHONY: install clean

include $(shell pwd)/../../config.mk
