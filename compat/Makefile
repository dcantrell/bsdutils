SRCS = setmode.c strmode.c merge.c heapsort.c
OBJS = $(SRCS:.c=.o)

all: libcompat.a

libcompat.a: $(OBJS)
	ar rcs $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -D_POSIX_C_SOURCE -D_GNU_SOURCE -D_DEFAULT_SOURCE -I../include -c -o $@ $<

check:

clean:
	-rm -f $(OBJS) libcompat.a

.PHONY: clean

include $(shell pwd)/../config.mk
