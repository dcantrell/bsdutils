#!/bin/sh
#
# Create patches for all files with a .orig pair, write to ./patches.
#

PATH=/bin:/usr/bin
CWD="$(pwd)"
BASEDIR="$(basename ${CWD})"

if [ "${BASEDIR}" = "compat" ]; then
    DESTDIR="$(realpath -m ${CWD}/../patches/compat)"
else
    DESTDIR="$(realpath -m ${CWD}/../../patches/src/${BASEDIR})"
fi

ls -1 *.orig 2>/dev/null | while read inputfile ; do
    ORIGFILE="$(basename $(realpath ${inputfile}))"
    FILE="$(basename ${ORIGFILE} .orig)"

    if [ -f "${ORIGFILE}" ] && [ -f "${FILE}" ]; then
        [ -d "${DESTDIR}" ] || mkdir -p "${DESTDIR}"
        echo "diff -u \"${ORIGFILE}\" \"${FILE}\" > \"${DESTDIR}/${FILE}.patch\""
        diff -u "${ORIGFILE}" "${FILE}" > "${DESTDIR}/${FILE}.patch"
    fi
done
