SRCS = comm.c
OBJS = $(SRCS:.c=.o)

all: comm

comm: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 comm $(DESTDIR)$(BINDIR)/comm
	install -D -m 0644 comm.1 $(DESTDIR)$(MANDIR)/man1/comm.1

clean:
	-rm -f $(OBJS) comm

.PHONY: install clean

include $(shell pwd)/../../config.mk
