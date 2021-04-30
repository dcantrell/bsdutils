SRCS = users.c
OBJS = $(SRCS:.c=.o)

all: users

users: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $<

%.o: %.c
	$(CXX) $(CXXFLAGS) -c -o $@ $<

install:
	install -D -m 0755 users $(DESTDIR)$(BINDIR)/users
	install -D -m 0644 users.1 $(DESTDIR)$(MANDIR)/man1/users.1

clean:
	-rm -f $(OBJS) users

.PHONY: install clean

include $(shell pwd)/../../config.mk
