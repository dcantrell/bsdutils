SRCS = nohup.c
OBJS = $(SRCS:.c=.o)

all: nohup

nohup: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 nohup $(DESTDIR)$(BINDIR)/nohup
	install -D -m 0644 nohup.1 $(DESTDIR)$(MANDIR)/man1/nohup.1

clean:
	-rm -f $(OBJS) nohup

.PHONY: install clean

include $(shell pwd)/../../config.mk
