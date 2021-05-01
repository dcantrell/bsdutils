SRCS = chown.c
OBJS = $(SRCS:.c=.o)

all: chown

chown: $(OBJS)
	$(CC) $(CFLAGS) -DUID_MAX=INT_MAX -DGID_MAX=INT_MAX -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -DUID_MAX=INT_MAX -DGID_MAX=INT_MAX -c -o $@ $<

install:
	install -D -m 0755 chown $(DESTDIR)$(SBINDIR)/chown
	ln -s $(SBINDIR)/chown $(DESTDIR)$(BINDIR)/chgrp
	install -D -m 0644 chown.8 $(DESTDIR)$(MANDIR)/man8/chown.8
	install -D -m 0644 chgrp.1 $(DESTDIR)$(MANDIR)/man1/chgrp.1

clean:
	-rm -f $(OBJS) chown

.PHONY: install clean

include $(shell pwd)/../../config.mk
