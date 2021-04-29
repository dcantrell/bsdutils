SRCS = dirname.c
OBJS = $(SRCS:.c=.o)

all: dirname

dirname: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

install:
	install -D -m 0755 dirname $(DESTDIR)$(BINDIR)/dirname

clean:
	-rm -f $(OBJS) dirname

.PHONY: install clean

include $(shell pwd)/../../config.mk
