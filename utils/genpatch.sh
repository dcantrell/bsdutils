#!/bin/sh
#
# For the given directory, generate a patch file for each
# file+origfile pair found and write it to the specified output
# directory.  If the output directory does not exist, create it.
#

PATH=/usr/bin

[ -z "$1" -o -z "$2" -o -z "$3" ] && {
# usage
  echo "Usage: $0 [directory] [orig file extension] [output directory] " 1>&2
  exit 1
}

: ${DIFF:=diff}
: ${GENPATCH_DIFF_ARGS:=-up}
: ${GENPATCH_DIFF_CHANGELOG_ARGS:=-U0}

OUTPUT_DIR="$(realpath $3)"
[ -d "${OUTPUT_DIR}" ] || mkdir -p "${OUTPUT_DIR}"

find $1 \( -name "*$2" -o -name ".*$2" \) -print | sort |
while read f; do
    U="${GENPATCH_DIFF_ARGS}"
    [ "$(basename ${f})" = "ChangeLog${2}" ] && U="${GENPATCH_DIFF_CHANGELOG_ARGS}"
    OF="${OUTPUT_DIR}/$(basename ${f}).patch"
    diffcmd="${DIFF} ${U} /dev/null ${f%$2}"
#    ${DIFF} ${U} $f `echo $f | sed s/$2\$//`
    [ -r "${f}" ] && diffcmd="${DIFF} ${U} ${f} ${f%$2}"
    echo "${diffcmd} > ${OF}"
    ${diffcmd} > ${OF}
done
