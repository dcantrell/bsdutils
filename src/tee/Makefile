SRCS = tee.c
OBJS = $(SRCS:.c=.o)

all: tee

tee: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 tee $(DESTDIR)$(BINDIR)/tee
	install -D -m 0644 tee.1 $(DESTDIR)$(MANDIR)/man1/tee.1

clean:
	-rm -f $(OBJS) tee

.PHONY: install clean

include $(shell pwd)/../../config.mk
