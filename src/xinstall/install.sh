#!/bin/sh

BINDIR="${1}"

mkdir -p "${DESTDIR}/${MESON_INSTALL_PREFIX}/${BINDIR}"
install -d "${DESTDIR}/${MESON_INSTALL_PREFIX}/${BINDIR}"
install -m 0755 ${MESON_BUILD_ROOT}/src/xinstall/xinstall "${DESTDIR}/${MESON_INSTALL_PREFIX}/${BINDIR}"/install
