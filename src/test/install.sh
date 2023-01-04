#!/bin/sh

BINDIR="${1}"

mkdir -p "${DESTDIR}/${MESON_INSTALL_PREFIX}/${BINDIR}"
install -d "${DESTDIR}/${MESON_INSTALL_PREFIX}/${BINDIR}"
install -m 0755 ${MESON_BUILD_ROOT}/src/test/xtest "${DESTDIR}/${MESON_INSTALL_PREFIX}/${BINDIR}"/test
ln -sf test "${DESTDIR}/${MESON_INSTALL_PREFIX}/${BINDIR}/["
install -d "${DESTDIR}/${MESON_INSTALL_PREFIX}/${MANDIR}"/man1
ln -sf test.1 "${DESTDIR}/${MESON_INSTALL_PREFIX}/${MANDIR}"/man1/"[.1"
