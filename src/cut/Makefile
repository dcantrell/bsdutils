SRCS = cut.c
OBJS = $(SRCS:.c=.o)

all: cut

cut: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 cut $(DESTDIR)$(BINDIR)/cut
	install -D -m 0644 cut.1 $(DESTDIR)$(MANDIR)/man1/cut.1

clean:
	-rm -f $(OBJS) cut

.PHONY: install clean

include $(shell pwd)/../../config.mk
