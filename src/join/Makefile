SRCS = join.c
OBJS = $(SRCS:.c=.o)

all: join

join: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 join $(DESTDIR)$(BINDIR)/join
	install -D -m 0644 join.1 $(DESTDIR)$(MANDIR)/man1/join.1

clean:
	-rm -f $(OBJS) join

.PHONY: install clean

include $(shell pwd)/../../config.mk
