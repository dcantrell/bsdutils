SRCS = cmp.c ls.c print.c util.c
HDRS = extern.h ls.h
OBJS = $(SRCS:.c=.o)

# Requires terminfo from the ncurses package
LIBS = ../../compat/libcompat.a -ltinfo

all: ls

ls: $(OBJS)
	$(CC) $(CFLAGS) -DCOLORLS -D_GNU_SOURCE -I../../include -o $@ $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -DCOLORLS -D_GNU_SOURCE -I../../include -c -o $@ $<

install:
	install -D -m 0755 ls $(DESTDIR)$(BINDIR)/ls
	install -D -m 0644 ls.1 $(DESTDIR)$(MANDIR)/man1/ls.1

clean:
	-rm -f $(OBJS) ls

.PHONY: install clean

include $(shell pwd)/../../config.mk
