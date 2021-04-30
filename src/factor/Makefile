SRCS = factor.c pr_tbl.c
HDRS = primes.h
OBJS = $(SRCS:.c=.o)

all: factor

factor: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 factor $(DESTDIR)$(BINDIR)/factor
	install -D -m 0644 factor.6 $(DESTDIR)$(MANDIR)/man6/factor.6

clean:
	-rm -f $(OBJS) factor

.PHONY: install clean

include $(shell pwd)/../../config.mk
