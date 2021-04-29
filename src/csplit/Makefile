SRCS = csplit.c
OBJS = $(SRCS:.c=.o)

all: csplit

csplit: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 csplit $(DESTDIR)$(BINDIR)/csplit
	install -D -m 0644 csplit.1 $(DESTDIR)$(MANDIR)/man1/csplit.1

clean:
	-rm -f $(OBJS) csplit

.PHONY: install clean

include $(shell pwd)/../../config.mk
