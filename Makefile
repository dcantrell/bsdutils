# bsdutils Makefile
# (assumed GNU make)

# Read in build settings
include config.mk

# Submakes need these settings
export CC CFLAGS

all:
	$(MAKE) -C compat
	$(MAKE) -C src

install:
	$(MAKE) -C src install

clean:
	$(MAKE) -C compat clean
	$(MAKE) -C src clean

.PHONY: all install clean
