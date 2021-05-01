SRCS = logname.c
OBJS = $(SRCS:.c=.o)

all: logname

logname: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 logname $(DESTDIR)$(BINDIR)/logname
	install -D -m 0644 logname.1 $(DESTDIR)$(MANDIR)/man1/logname.1

clean:
	-rm -f $(OBJS) logname

.PHONY: install clean

include $(shell pwd)/../../config.mk
