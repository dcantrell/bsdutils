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

When a new release of FreeBSD is made, the 'make import' target should
be used.

1) Create a new branch to do the import work.  The convention is to make
   the branch from main and name it after the FreeBSD release you are
   importing from.  For example, branch 13.2-RELEASE when importing from
   13.2-RELEASE.

2) Switch to this new branch.

3) Change VER in upstream.conf to match what you are importing, e.g.
   13.2-RELEASE.

4) Verify URL in upstream.conf works (FreeBSD may move things around).

5) Run 'make import'

NOTE: 'make import' may fail if the source tree has been reorganized.
For example, in 13.2-RELEASE the timeout(1) command source moved from
usr.bin/timeout to bin/timeout.  Look for these failures and modify
utils/import-src.sh as necessary.  Do a 'git checkout -- src && git
checkout -- compat' and run the import process again until it
succeeds.

6) Commit all these changes on the branch.  And tag the branch as the
   import point.  e.g., for 13.2-RELEASE the tag would be:

       git tag -s 13.2-RELEASE-import

   NOTE:  Be sure to not commit the Makefile.bsd files.

7) Now bring all the patches forward that get it working on Linux.  To
   do this I generate a diff from the previous import point to the tagged
   release.  For example, for 13.1-RELEASE, I do:

       git diff 13.1-RELEASE-import v13.1 > ~/patches
       cd ~
       mkdir p
       cd p
       splitdiff -a -d ../patches

   From here I begin building bsdutils on the branch and bringing over
   patches as needed.  Some may no longer be valid.  There may need to be
   meson.build file changes too if new source files have been introduced.
   This is the trial and error part of porting, but should not take long.

8) Once bsdutils builds on the branch, commit the changes on the
   branch.  Push to upstream.

9) Now on main, merge the 13.2-RELEASE branch on to main.  Once you have
   done that, make sure it builds again and tag it:

       git tag -s v13.2

   The main branch now contains the latest stable released bsdutils.

Push the changes and check that CI passes.  After some testing, it's
probably time for a release.


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
