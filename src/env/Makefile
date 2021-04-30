SRCS = env.c envopts.c
HDRS = envopts.h
OBJS = $(SRCS:.c=.o)

all: env

env: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 env $(DESTDIR)$(BINDIR)/env
	install -D -m 0644 env.1 $(DESTDIR)$(MANDIR)/man1/env.1

clean:
	-rm -f $(OBJS) env

.PHONY: install clean

include $(shell pwd)/../../config.mk
