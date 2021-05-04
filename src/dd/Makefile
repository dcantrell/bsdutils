SRCS = args.c conv.c conv_tab.c dd.c misc.c position.c
HDRS = dd.h extern.h
OBJS = $(SRCS:.c=.o)

LIBS = ../../compat/libcompat.a

all: dd

dd: $(OBJS)
	$(CC) $(CFLAGS) -D_GNU_SOURCE -I../../include -o $@ $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -D_GNU_SOURCE -I../../include -c -o $@ $<

install:
	install -D -m 0755 dd $(DESTDIR)$(BINDIR)/dd
	install -D -m 0644 dd.1 $(DESTDIR)$(MANDIR)/man1/dd.1

clean:
	-rm -f $(OBJS) dd

.PHONY: install clean

include $(shell pwd)/../../config.mk
