SRCS = cat.c
OBJS = cat.o

all: cat

cat: $(OBJS)
	$(CC) $(CFLAGS) -DNO_UDOM_SUPPORT -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -DNO_UDOM_SUPPORT -c -o $@ $<

install:
	install -D -m 0755 cat $(DESTDIR)$(BINDIR)/cat
	install -D -m 0644 cat.1 $(DESTDIR)$(MANDIR)/man1/cat.1

clean:
	-rm -f $(OBJS) cat

.PHONY: install clean

include $(shell pwd)/../../config.mk
