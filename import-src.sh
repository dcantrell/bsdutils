#!/bin/sh
#
# import-src.sh - Import specific release of FreeBSD source in to
#                 this tree.  Primarily for maintenance use when
#                 a new version of FreeBSD comes out.
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

for sub in src ; do
   [ -d ${CWD}/${sub} ] || mkdir -p ${CWD}/${sub}
done

cd ${TMPDIR}
curl -L --retry 3 --ftp-pasv -O ${SRC} || fail_exit
xz -dc src.txz | tar -xf -

# XXX: commands
#usr.bin/arch
#usr.bin/readlink  (part of stat)

# copy in the source for all coreutils programs
CMDS="bin/test
      usr.bin/basename
      usr.bin/bc
      bin/cat
      bin/chmod
      usr.sbin/chown
      usr.bin/cksum
      usr.bin/comm
      bin/cp
      usr.bin/csplit
      usr.bin/cut
      bin/date
      usr.bin/dc
      bin/dd
      bin/df
      usr.bin/dirname
      usr.bin/du
      bin/echo
      usr.bin/env
      usr.bin/expand
      bin/expr
      usr.bin/factor
      usr.bin/false
      usr.bin/find
      usr.bin/fmt
      usr.bin/fold
      usr.bin/head
      bin/hostname
      usr.bin/id
      usr.bin/join
      bin/ln
      usr.bin/logname
      bin/ls
      bin/mkdir
      sbin/mknod
      usr.bin/mktemp
      usr.bin/mkfifo
      bin/mv
      usr.bin/nice
      usr.bin/nl
      usr.bin/nohup
      usr.bin/paste
      usr.bin/pr
      usr.bin/printenv
      usr.bin/printf
      bin/pwd
      bin/realpath
      bin/rm
      bin/rmdir
      usr.bin/seq
      bin/sleep
      usr.bin/sort
      usr.bin/split
      usr.bin/stat
      usr.bin/stdbuf
      bin/stty
      bin/sync
      usr.bin/tail
      usr.bin/tee
      usr.bin/timeout
      usr.bin/touch
      usr.bin/tr
      usr.bin/true
      usr.bin/truncate
      usr.bin/tsort
      usr.bin/tty
      usr.bin/uname
      usr.bin/unexpand
      usr.bin/uniq
      usr.bin/users
      usr.bin/wc
      usr.bin/which
      usr.bin/who
      usr.bin/yes
      usr.sbin/chroot
      usr.bin/xargs
      usr.bin/xinstall"
for p in ${CMDS} ; do
    rp="usr/src/${p}"
    sp="$(basename ${p})"

    # Drop the tests/ subdirectories
    [ -d ${rp}/tests ] && rm -rf ${rp}/tests

    # Rename the upstream Makefile for later manual checking.  We don't
    # commit these to our tree, but just look at them when rebasing and
    # pick up any rule changes to put in our Makefile.am files.
    if [ -f "${rp}/Makefile" ]; then
        mv ${rp}/Makefile ${rp}/Makefile.bsd
    fi

    # Drop the Makefile.depend* files
    rm -f ${rp}/Makefile.depend*

    # Copy in the upstream files
    [ -d ${CWD}/src/${sp} ] || mkdir -p ${CWD}/src/${sp}
    cp -pr ${rp}/* ${CWD}/src/${sp}
done

# 'compat' is our static library with a subset of BSD library functions
cp -p usr/src/lib/libc/gen/setmode.c ${CWD}/compat
cp -p usr/src/lib/libc/string/strmode.c ${CWD}/compat
cp -p usr/src/lib/libc/gen/getbsize.c ${CWD}/compat
cp -p usr/src/lib/libutil/humanize_number.c ${CWD}/compat
cp -p usr/src/lib/libutil/expand_number.c ${CWD}/compat
cp -p usr/src/lib/libc/stdlib/merge.c ${CWD}/compat
cp -p usr/src/lib/libc/stdlib/heapsort.c ${CWD}/compat
cp -p usr/src/contrib/libc-vis/vis.c ${CWD}/compat
cp -p usr/src/contrib/libc-vis/vis.h ${CWD}/include

# These files are needed for the factor command
cp -p usr/src/usr.bin/primes/primes.h ${CWD}/src/factor
cp -p usr/src/usr.bin/primes/pr_tbl.c ${CWD}/src/factor

# These files are needed for the df command
cp -p usr/sbin/sbin/mount/vfslist.c ${CWD}/src/df

#####################
# APPLY ANY PATCHES #
#####################

if [ -d ${CWD}/patches/compat ]; then
    for patchfile in ${CWD}/patches/compat/*.patch ; do
        destfile="$(basename ${patchfile} .patch)"
        [ -f "${CWD}/compat/${destfile}.orig" ] && rm -f "${CWD}/compat/${destfile}.orig"
        patch -d ${CWD} -p0 -b -z .orig < ${patchfile}
    done
fi

if [ -d ${CWD}/patches/src ]; then
    cd ${CWD}/patches/src
    for subdir in * ; do
        [ -d ${subdir} ] || continue
        for patchfile in ${CWD}/patches/src/${subdir}/*.patch ; do
            destfile="$(basename ${patchfile} .patch)"
            [ -f "${CWD}/src/${subdir}/${destfile}.orig" ] && rm -f "${CWD}/src/${subdir}/${destfile}.orig"
            patch -d ${CWD}/src -p0 -b -z .orig < ${patchfile}
        done
    done
fi

# Clean up
rm -rf ${TMPDIR}
