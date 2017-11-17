#!/bin/sh
#
# import-src.sh - Import specific release of OpenBSD source in to
#                 this tree.  Primarily for maintenance use when
#                 a new version of OpenBSD comes out.
#
# Author: David Cantrell <david.l.cantrell@gmail.com>
#

PATH=/bin:/usr/bin
CWD="$(pwd)"
TMPDIR="$(mktemp -d --tmpdir=${CWD})"
. ${CWD}/upstream.conf

fail_exit() {
    cd ${CWD}
    rm -rf ${TMPDIR}
    exit 1
}

for sub in compat lib src ; do
    [ -d ${CWD}/${sub} ] || mkdir -p ${CWD}/${sub}
done

cd ${TMPDIR}
curl -L --retry 3 --ftp-pasv -O ${SRC} || fail_exit
gzip -dc src.tar.gz | tar -xvf -

# copy in the source for all coreutils programs
CMDS="bin/test
      usr.bin/arch
      usr.bin/basename
      bin/cat
      bin/chmod
      usr.bin/comm
      bin/cp
      usr.bin/csplit
      usr.bin/cut
      bin/date
      bin/dd
      bin/df
      usr.bin/dirname
      usr.bin/du
      bin/echo
      usr.bin/env
      usr.bin/expand
      bin/expr
      games/factor
      usr.bin/false
      usr.bin/fmt
      usr.bin/fold
      usr.bin/head
      usr.bin/id
      usr.bin/join
      bin/ln
      usr.bin/logname
      bin/ls
      bin/mkdir
      sbin/mknod
      usr.bin/mktemp
      bin/mv
      usr.bin/nice
      usr.bin/nl
      usr.bin/nohup
      usr.bin/paste
      usr.bin/pr
      usr.bin/printenv
      usr.bin/printf
      bin/pwd
      usr.bin/readlink
      bin/rm
      bin/rmdir
      bin/sleep
      usr.bin/sort
      usr.bin/split
      usr.bin/stat
      bin/stty
      bin/sync
      usr.bin/tail
      usr.bin/tee
      usr.bin/touch
      usr.bin/tr
      usr.bin/true
      usr.bin/tsort
      usr.bin/tty
      usr.bin/uname
      usr.bin/unexpand
      usr.bin/uniq
      usr.bin/users
      usr.bin/wc
      usr.bin/who
      usr.bin/yes
      usr.sbin/chroot"
for p in ${CMDS} ; do
    sp="$(basename ${p})"
    find ${p} -type d -name CVS | xargs rm -rf

    # Rename the upstream Makefile for later manual checking.  We don't
    # commit these to our tree, but just look at them when rebasing and
    # pick up any rule changes to put in our Makefile.am files.
    if [ -f "${p}/Makefile" ]; then
        mv ${p}/Makefile ${p}/Makefile.bsd
    fi

    # Copy in the upstream files
    [ -d ${CWD}/src/${sp} ] || mkdir -p ${CWD}/src/${sp}
    cp -pr ${p}/* ${CWD}/src/${sp}
done
exit 0

# We need libutil to build some things
cp -pr lib/libutil/* ${CWD}/lib

# 'compat' is our static library with a subset of BSD library functions
cp -p lib/libc/gen/pwcache.c ${CWD}/compat
cp -p lib/libc/gen/setmode.c ${CWD}/compat
cp -p lib/libc/gen/getbsize.c ${CWD}/compat
cp -p lib/libc/stdlib/reallocarray.c ${CWD}/compat
cp -p lib/libc/stdlib/strtonum.c ${CWD}/compat
cp -p lib/libc/string/strlcat.c ${CWD}/compat
cp -p lib/libc/string/strlcpy.c ${CWD}/compat
cp -p lib/libc/string/strmode.c ${CWD}/compat
cp -p lib/libutil/logwtmp.c ${CWD}/compat
cp -p lib/libutil/ohash.c ${CWD}/compat
cp -p lib/libutil/ohash.h ${CWD}/compat
cp -p lib/libutil/fmt_scaled.h ${CWD}/compat

# These files are needed for the factor command
cp -p games/primes/primes.h ${CWD}/src/factor
cp -p games/primes/pattern.c ${CWD}/src/factor
cp -p games/primes/pr_tbl.c ${CWD}/src/factor

# Clean up
rm -rf ${TMPDIR}
