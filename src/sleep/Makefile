SRCS = sleep.c
OBJS = $(SRCS:.c=.o)

all: sleep

sleep: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 sleep $(DESTDIR)$(BINDIR)/sleep
	install -D -m 0644 sleep.1 $(DESTDIR)$(MANDIR)/man1/sleep.1

clean:
	-rm -f $(OBJS) sleep

.PHONY: install clean

include $(shell pwd)/../../config.mk
