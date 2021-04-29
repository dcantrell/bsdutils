SRCS = echo.c
OBJS = $(SRCS:.c=.o)

all: echo

echo: $(OBJS)
	$(CC) $(CFLAGS) -D_XOPEN_SOURCE -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -D_XOPEN_SOURCE -c -o $@ $<

install:
	install -D -m 0755 echo $(DESTDIR)$(BINDIR)/echo
	install -D -m 0644 echo.1 $(DESTDIR)$(MANDIR)/man1/echo.1

clean:
	-rm -f $(OBJS) echo

.PHONY: install clean

include $(shell pwd)/../../config.mk
