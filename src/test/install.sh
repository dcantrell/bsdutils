#!/bin/sh

BINDIR="${1}"

mkdir -p "${DESTDIR}/${MESON_INSTALL_PREFIX}${BINDIR}"
install -D -m 0755 ${MESON_BUILD_ROOT}/src/test/xtest "${DESTDIR}/${MESON_INSTALL_PREFIX}${BINDIR}"/test
