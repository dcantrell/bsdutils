SRCS = id.c
OBJS = $(SRCS:.c=.o)

all: id

id: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 id $(DESTDIR)$(BINDIR)/id
	ln -s $(BINDIR)/id $(DESTDIR)$(BINDIR)/groups
	ln -s $(BINDIR)/id $(DESTDIR)$(BINDIR)/whoami
	install -D -m 0644 id.1 $(DESTDIR)$(MANDIR)/man1/id.1
	install -D -m 0644 id.1 $(DESTDIR)$(MANDIR)/man1/groups.1
	install -D -m 0644 id.1 $(DESTDIR)$(MANDIR)/man1/whoami.1

clean:
	-rm -f $(OBJS) id

.PHONY: install clean

include $(shell pwd)/../../config.mk
