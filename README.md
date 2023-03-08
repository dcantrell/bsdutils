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

3) Run ./import-src.sh.

4) Do an initial commit of this import and tag it as
   X.Y-RELEASE-import.  For example, importing source from FreeBSD 13.1
   would have a tag named 13.1-RELEASE-import in the tree.

   * NOTE: The tree should have Makefile.bsd files in it right now,
     but those should not be committed.  Leave them in place for now.

5) Use git to gather the changes between the previous
   X.[Y-1]-RELEASE-import tag and the previous commit.  Apply these to
   the tree now.  This is mostly easy, but some patches will have to
   be manually applied.  What I tend to do is generate a large patch
   with git and then run splitdiff on that to get individual patches
   for each source file.  I then have a script that tries to apply
   each of those and for any that fail, I retain them.  If the patch
   applied successfully, I remove the patch.  The remaining set I need
   to apply by hand.

6) After applying patches, run make.  Fix anything that fails.  This
   is the step that updates the patches for the new FreeBSD source.

7) Now check each Makefile.bsd file to see if our meson.build files
   need updating.  There may be new compiler flags or macros to
   define.  Likewise there may be new source files that should be
   listed.  Use this step to also remove any source files that no
   longer exist (the Makefile.bsd file won't reference the file, so
   you can remove it and update the meson.build file).

8) Now commit these changes.

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
    libxo          https://github.com/Juniper/libxo

    openssl        https://www.openssl.org/ OR
    libressl       https://www.libressl.org/

On MacOS, if you have libressl or openssl installed via a package manager
other than [brew](https://formulae.brew.sh/) the build system might not find
all required libraries. If this is the case, please open a ticket.

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
