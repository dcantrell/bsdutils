SRCS = printf.c
OBJS = $(SRCS:.c=.o)

all: printf

printf: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 printf $(DESTDIR)$(BINDIR)/printf
	install -D -m 0644 printf.1 $(DESTDIR)$(MANDIR)/man1/printf.1

clean:
	-rm -f $(OBJS) printf

.PHONY: install clean

include $(shell pwd)/../../config.mk
