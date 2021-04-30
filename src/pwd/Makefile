SRCS = pwd.c
OBJS = $(SRCS:.c=.o)

all: pwd

pwd: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 pwd $(DESTDIR)$(BINDIR)/pwd
	install -D -m 0644 pwd.1 $(DESTDIR)$(MANDIR)/man1/pwd.1

clean:
	-rm -f $(OBJS) pwd

.PHONY: install clean

include $(shell pwd)/../../config.mk
