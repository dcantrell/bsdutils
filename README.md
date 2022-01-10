## bsdutils

This project contains a GNU coreutils-like collection of utilities
from the FreeBSD source code tree.

The project began in October 2017 and initially ported code from the
OpenBSD source tree.  The original objective was to see how much work
was involved and to compare relative sizes of built executables with
those found in GNU coreutils and other projects.  In an effort to gain
more featureful BSD commands and to possibly work more easily with
dotfiles for users on MacOS X systems, the project started over by
porting the commands from FreeBSD in April 2021.


Importing A New Release Of FreeBSD
----------------------------------

When a new release of FreeBSD is made, the import-src.sh script should
be used to update the source tree.  First edit upstream.conf and then
run the import-src.sh script.  The script will fetch the new release
source and copy in the source for the commands we have.  Any patches
in patches/ will be applied.  These may need updating between
releases, so keep that in mind.  The workflow is basically:

1) Change VER in upstream.conf

2) Verify URL in upstream.conf works (FreeBSD may move things around).

3) Run ./import-src.sh.  It is adviseable to capture stdout and stderr
to see what patches fail to apply.  Any that fail, you want to
manually fix and then run import-src.sh again to get a clean import of
the version you are updating to.

4) Now build all the commands and fix any new build errors.

Once this is clean, you can commit the import of the new version of
FreeBSD code.  The import-src.sh and patches step is meant to make it
more clear what changes I apply to FreeBSD code from release to
release and also if any external projects want to use these patches
and the FreeBSD source directly.


Build Requirements
------------------

You will need GNU-compatible C and C++ compilers, typically gcc/g++
or clang/clang++. You will also need flex (or some other lex as long
as it is compatible with flex), byacc or bison, meson and ninja/samurai.
If you wish to use the top-level Makefile (which is just a simple
wrapper around meson), you will need GNU make. Most distributions
have all these tools already available in their repositories.

    gcc/g++        https://gcc.gnu.org/
    clang/clang++  https://llvm.org/
    GNU make       https://www.gnu.org/software/make/
    meson          https://mesonbuild.com/
    ninja          https://ninja-build.org/
    flex           https://github.com/westes/flex
    byacc          https://invisible-island.net/byacc/byacc.html

Additionally you will need the following shared libraries to build all
of the programs in this project:

    terminfo       https://invisible-mirror.net/archives/ncurses/
    libedit        http://thrysoee.dk/editline/
    openssl        https://www.openssl.org/
    libxo          https://github.com/Juniper/libxo

The terminfo library may be either standalone (libtinfo) or a part
of the curses library, dependending on build. The ls(1) command needs
this.  bc(1) needs libedit, which is the BSD alternative to GNU
readline.  dc(1) uses libcrypto which comes from OpenSSL.  seq(1)
needs libm, but that comes from your C library.  df(1) and wc(1) use
libxo for outputting to multiple formats.

Users of musl-based Linux systems also need libfts and librpmatch
installed.


Bugs
----

Probably.  The FreeBSD code is pretty solid.  But remember this
project is a port of that code to Linux systems.  Pull requests
welcome for any bugs found.  Also you can just open an issue on the
project page and we will try to get to it.
