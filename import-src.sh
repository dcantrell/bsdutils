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
cp -pr bin/test ${CWD}/src
cp -pr usr.bin/arch ${CWD}/src
cp -pr usr.bin/basename ${CWD}/src
cp -pr bin/cat ${CWD}/src
cp -pr bin/chmod ${CWD}/src
cp -pr usr.bin/comm ${CWD}/src
cp -pr bin/cp ${CWD}/src
cp -pr usr.bin/csplit ${CWD}/src
cp -pr usr.bin/cut ${CWD}/src
cp -pr bin/date ${CWD}/src
cp -pr bin/dd ${CWD}/src
cp -pr bin/df ${CWD}/src
cp -pr usr.bin/dirname ${CWD}/src
cp -pr usr.bin/du ${CWD}/src
cp -pr bin/echo ${CWD}/src
cp -pr usr.bin/env ${CWD}/src
cp -pr usr.bin/expand ${CWD}/src
cp -pr bin/expr ${CWD}/src
cp -pr games/factor ${CWD}/src
cp -pr usr.bin/false ${CWD}/src
cp -pr usr.bin/fmt ${CWD}/src
cp -pr usr.bin/fold ${CWD}/src
cp -pr usr.bin/head ${CWD}/src
cp -pr usr.bin/id ${CWD}/src
cp -pr usr.bin/join ${CWD}/src
cp -pr bin/ln ${CWD}/src
cp -pr usr.bin/logname ${CWD}/src
cp -pr bin/ls ${CWD}/src
cp -pr bin/mkdir ${CWD}/src
cp -pr sbin/mknod ${CWD}/src
cp -pr usr.bin/mktemp ${CWD}/src
cp -pr bin/mv ${CWD}/src
cp -pr usr.bin/nice ${CWD}/src
cp -pr usr.bin/nl ${CWD}/src
cp -pr usr.bin/nohup ${CWD}/src
cp -pr usr.bin/paste ${CWD}/src
cp -pr usr.bin/pr ${CWD}/src
cp -pr usr.bin/printenv ${CWD}/src
cp -pr usr.bin/printf ${CWD}/src
cp -pr bin/pwd ${CWD}/src
cp -pr usr.bin/readlink ${CWD}/src
cp -pr bin/rm ${CWD}/src
cp -pr bin/rmdir ${CWD}/src
cp -pr bin/sleep ${CWD}/src
cp -pr usr.bin/sort ${CWD}/src
cp -pr usr.bin/split ${CWD}/src
cp -pr usr.bin/stat ${CWD}/src
cp -pr bin/stty ${CWD}/src
cp -pr bin/sync ${CWD}/src
cp -pr usr.bin/tail ${CWD}/src
cp -pr usr.bin/tee ${CWD}/src
cp -pr usr.bin/touch ${CWD}/src
cp -pr usr.bin/tr ${CWD}/src
cp -pr usr.bin/true ${CWD}/src
cp -pr usr.bin/tsort ${CWD}/src
cp -pr usr.bin/tty ${CWD}/src
cp -pr usr.bin/uname ${CWD}/src
cp -pr usr.bin/unexpand ${CWD}/src
cp -pr usr.bin/uniq ${CWD}/src
cp -pr usr.bin/users ${CWD}/src
cp -pr usr.bin/wc ${CWD}/src
cp -pr usr.bin/who ${CWD}/src
cp -pr usr.bin/yes ${CWD}/src
cp -pr usr.sbin/chroot ${CWD}/src

# We need libutil to build some things
cp -pr lib/libutil/* ${CWD}/lib

# 'compat' is our static library with a subset of BSD library functions
cp -p lib/libc/gen/setmode.c ${CWD}/compat
cp -p lib/libc/stdlib/reallocarray.c ${CWD}/compat

# Dump the trash
find ${CWD}/src -type d -name CVS | xargs rm -rf
find ${CWD}/src -type f -name Makefile | xargs rm -f

# Clean up
rm -rf ${TMPDIR}
