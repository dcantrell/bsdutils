# bsdutils Makefile
# (assumed GNU make)

# Read in build settings
include config.mk

# Submakes need these settings
export CC CFLAGS

all:
	$(MAKE) -C compat
	$(MAKE) -C src

check: all
	$(MAKE) -C compat check
	$(MAKE) -C src check

install: all
	$(MAKE) -C src install

clean:
	$(MAKE) -C compat clean
	$(MAKE) -C src clean

.PHONY: all install clean
