SRCS = false.c
OBJS = $(SRCS:.c=.o)

all: false

false: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 false $(DESTDIR)$(BINDIR)/false
	install -D -m 0644 false.1 $(DESTDIR)$(MANDIR)/man1/false.1

clean:
	-rm -f $(OBJS) false

.PHONY: install clean

include $(shell pwd)/../../config.mk
