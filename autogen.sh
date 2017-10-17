#!/bin/sh
libtoolize --copy --force
aclocal
autoconf
autoheader --force
automake --foreign --add-missing --copy
rm -rf autom4te.cache
