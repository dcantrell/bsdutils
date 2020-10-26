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

for sub in compat src ; do
    [ -d ${CWD}/${sub} ] || mkdir -p ${CWD}/${sub}
done

cd ${TMPDIR}
curl -L --retry 3 --ftp-pasv -O ${SRC} || fail_exit
curl -L --retry 3 --ftp-pasv -O ${SYS} || fail_exit
gzip -dc src.tar.gz | tar -xf -
gzip -dc sys.tar.gz | tar -xf -

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
      usr.sbin/chroot
      usr.bin/xargs
      usr.bin/xinstall"
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

# Explicit removals for things that Linux does not support
rm ${CWD}/src/chmod/chflags.1
rm ${CWD}/src/df/ext2fs_df.c
rm ${CWD}/src/df/ffs_df.c

# 'compat' is our static library with a subset of BSD library functions
cp -p lib/libc/gen/pwcache.c ${CWD}/compat
cp -p lib/libc/gen/setmode.c ${CWD}/compat
cp -p lib/libc/gen/getbsize.c ${CWD}/compat
cp -p lib/libc/gen/devname.c ${CWD}/compat
cp -p lib/libc/stdlib/merge.c ${CWD}/compat
cp -p lib/libc/stdlib/recallocarray.c ${CWD}/compat
cp -p lib/libc/stdlib/strtonum.c ${CWD}/compat
cp -p lib/libc/string/strlcat.c ${CWD}/compat
cp -p lib/libc/string/strlcpy.c ${CWD}/compat
cp -p lib/libc/string/strmode.c ${CWD}/compat
cp -p lib/libutil/ohash.c ${CWD}/compat
cp -p lib/libutil/ohash.h ${CWD}/compat
cp -p lib/libutil/fmt_scaled.c ${CWD}/compat
cp -p lib/libutil/util.h ${CWD}/compat

# These files are needed for the factor command
cp -p games/primes/primes.h ${CWD}/src/factor
cp -p games/primes/pattern.c ${CWD}/src/factor
cp -p games/primes/pr_tbl.c ${CWD}/src/factor

# This header is in the kernel source, but used in userspace
cp -p sys/sys/tree.h ${CWD}/compat/tree.h

################
# COMMON EDITS #
################

# Perform some common compatibility edits on the imported source
for cfile in ${CWD}/compat/*.c ; do
    # This macro does not exist and we don't want it
    sed -i -e '/DEF_WEAK/d' ${cfile}

    # Include our 'compat.h' header before other includes
    if ! grep -q "compat\.h" ${cfile} 2>&1 ; then
        linenum=$(($(grep -n ^#include ${cfile} | sort -n | head -n 1 | cut -d ':' -f 1) - 1))
        [ ${linenum} = 0 ] && linenum=1
        sed -i -e "${linenum}i #include \"compat.h\"" ${cfile}
    fi
done

# Remove unnecessary declarations in compat/util.h
strtline=$(grep -n "^__BEGIN_DECLS" ${CWD}/compat/util.h | cut -d ':' -f 1)
lastline=$(grep -n "^__END_DECLS" ${CWD}/compat/util.h | cut -d ':' -f 1)
sed -i -e "${strtline},${lastline}d" ${CWD}/compat/util.h

# Common edits needed for src/ files
for cfile in $(find ${CWD}/src -type f -name '*.c' -print) ; do
    # remove __dead
    sed -i -r 's|\s+__dead\s+| |g' ${cfile}
    sed -i -r 's|^__dead\s+||g' ${cfile}
    sed -i -r 's|\s+__dead$||g' ${cfile}
    sed -i -r 's|\s+__dead;|;|g' ${cfile}
done

#####################
# APPLY ANY PATCHES #
#####################

if [ -d ${CWD}/patches/compat ]; then
    for patchfile in ${CWD}/patches/compat/*.patch ; do
        destfile="$(basename ${patchfile} .patch)"
        [ -f "${CWD}/compat/${destfile}.orig" ] && rm -f "${CWD}/compat/${destfile}.orig"
        patch -d ${CWD}/compat -p0 -b -z .orig < ${patchfile}
    done
fi

if [ -d ${CWD}/patches/src ]; then
    cd ${CWD}/patches/src
    for subdir in * ; do
        [ -d ${subdir} ] || continue
        for patchfile in ${CWD}/patches/src/${subdir}/*.patch ; do
            destfile="$(basename ${patchfile} .patch)"
            [ -f "${CWD}/src/${subdir}/${destfile}.orig" ] && rm -f "${CWD}/src/${subdir}/${destfile}.orig"
            patch -d ${CWD}/src/${subdir} -p0 -b -z .orig < ${patchfile}
        done
    done
fi

# Clean up
rm -rf ${TMPDIR}
