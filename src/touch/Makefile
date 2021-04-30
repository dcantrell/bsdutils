SRCS = touch.c
OBJS = $(SRCS:.c=.o)

all: touch

touch: $(OBJS)
	$(CC) $(CFLAGS) -D_GNU_SOURCE -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -D_GNU_SOURCE -c -o $@ $<

install:
	install -D -m 0755 touch $(DESTDIR)$(BINDIR)/touch
	install -D -m 0644 touch.1 $(DESTDIR)$(MANDIR)/man1/touch.1

clean:
	-rm -f $(OBJS) touch

.PHONY: install clean

include $(shell pwd)/../../config.mk
