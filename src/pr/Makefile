SRCS = egetopt.c pr.c
HDRS = extern.h pr.h
OBJS = $(SRCS:.c=.o)

all: pr

pr: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 pr $(DESTDIR)$(BINDIR)/pr
	install -D -m 0644 pr.1 $(DESTDIR)$(MANDIR)/man1/pr.1

clean:
	-rm -f $(OBJS) pr

.PHONY: install clean

include $(shell pwd)/../../config.mk
