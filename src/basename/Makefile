SRCS = basename.c
OBJS = $(SRCS:.c=.o)

all: basename

basename: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 basename $(DESTDIR)$(BINDIR)/basename
	install -D -m 0644 basename.1 $(DESTDIR)$(MANDIR)/man1/basename.1

clean:
	-rm -f $(OBJS) basename

.PHONY: install clean

include $(shell pwd)/../../config.mk
