SRCS = mkdir.c
OBJS = $(SRCS:.c=.o)

LIBS = ../../compat/libcompat.a

all: mkdir

mkdir: $(OBJS)
	$(CC) $(CFLAGS) -I../../include -o $@ $< $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -I../../include -c -o $@ $<

install:
	install -D -m 0755 mkdir $(DESTDIR)$(BINDIR)/mkdir
	install -D -m 0644 mkdir.1 $(DESTDIR)$(MANDIR)/man1/mkdir.1

clean:
	-rm -f $(OBJS) mkdir

.PHONY: install clean

include $(shell pwd)/../../config.mk
