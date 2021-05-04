#!/bin/sh
#
# Find the ninja command to use.
#

if ! ninja --help >/dev/null 2>&1 ; then
    echo "ninja"
    exit 0
fi

if ! ninja-build --help >/dev/null 2>&1 ; then
    echo "ninja-build"
    exit 0
fi

exit 1
