SRCS = yes.c
OBJS = $(SRCS:.c=.o)

all: yes

yes: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 yes $(DESTDIR)$(BINDIR)/yes
	install -D -m 0644 yes.1 $(DESTDIR)$(MANDIR)/man1/yes.1

clean:
	-rm -f $(OBJS) yes

.PHONY: install clean

include $(shell pwd)/../../config.mk
