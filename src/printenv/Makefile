SRCS = printenv.c
OBJS = $(SRCS:.c=.o)

all: printenv

printenv: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 printenv $(DESTDIR)$(BINDIR)/printenv
	install -D -m 0644 printenv.1 $(DESTDIR)$(MANDIR)/man1/printenv.1

clean:
	-rm -f $(OBJS) printenv

.PHONY: install clean

include $(shell pwd)/../../config.mk
