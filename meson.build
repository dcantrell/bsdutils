project('bsdutils',
        [ 'c', 'cpp' ],
        version : '1.0',
        default_options : [
            'c_std=c99',
            'warning_level=2',
            'buildtype=debugoptimized'
        ],
        license : 'BSD-3-Clause')

# Start with compilers for C and C++
cc = meson.get_compiler('c')
cpp = meson.get_compiler('cpp')

# FreeBSD code sometimes ignores things
add_global_arguments([ '-Wno-unused-result' ], language : [ 'c', 'cpp' ])

# Find lex
lex_prog = find_program('flex', 'lex', required : true)
lex = generator(
    lex_prog,
    output : [ '@BASENAME@.c' ],
    arguments: [ '-o', '@OUTPUT0@', '@INPUT@' ],
)

# Find yacc
# (With help from libxkbcommon at https://github.com/xkbcommon/libxkbcommon)
byacc = find_program('byacc', required : false)
if byacc.found()
    yacc = generator(
        byacc,
        output : [ '@BASENAME@.c', '@BASENAME@.h' ],
        arguments: [ '-H', '@OUTPUT1@', '-o', '@OUTPUT0@', '@INPUT@' ],
    )
else
    bison = find_program('bison', required : false)
    if bison.found()
        yacc = generator(
            bison,
            output: [ '@BASENAME@.c', '@BASENAME@.h' ],
            arguments: [ '--defines=@OUTPUT1@', '-o', '@OUTPUT0@', '@INPUT@' ],
        )
    else
        error('Could not find a compatible yacc(1) program (bison or byacc)')
    endif
endif

# Define some macros to eliminate some FreeBSD-specifics in the code
add_global_arguments(
    [ '-Dlint',
      '-DDEFFILEMODE=(S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)',
      '-DALLPERMS=(S_ISUID|S_ISGID|S_ISVTX|S_IRWXU|S_IRWXG|S_IRWXO)',
      '-DO_FSYNC=O_SYNC',
      '-DREG_STARTEND=0',
    ],
    language : [ 'c', 'cpp' ]
)

if not cc.has_function('strtoq')
   add_global_arguments([ '-Dstrtoq=strtoull' ], language : [ 'c', 'cpp' ])
endif

# Build everything with _GNU_SOURCE enabled
add_global_arguments('-D_GNU_SOURCE', language : [ 'c', 'cpp' ])

# Always use 64-bit file offsets on glibc
add_global_arguments('-D_FILE_OFFSET_BITS=64', language : [ 'c', 'cpp' ])

# ls(1) needs the terminfo library
foreach opt : ['tinfo', 'ncursesw', 'ncurses']
    libtinfo = cc.find_library(opt, required : false)
    if libtinfo.found()
        break
    endif
endforeach
if not libtinfo.found()
    error('a terminfo library is needed')
endif

# bc(1) needs libedit
libedit = dependency('libedit', required : true)

# dc(1) and install(1) need libcrypto
libcrypto = dependency('libcrypto', required : true)

# seq(1) needs libm
libm = cc.find_library('m', required : true)

# df(1) needs libxo
libxo = dependency('libxo', required : true)

# needed by a few utils; provided by glibc, but not by e.g. musl
libfts = cc.find_library('fts', required : false)
librpmatch = cc.find_library('rpmatch', required : false)

# sort needs pthreads
libpthread = dependency('threads')

# Header files for libcompat
inc = include_directories('include')

# Symlink installation script
install_link = meson.current_source_dir() / 'utils/install-link.sh'

# Include all of the relevant subdirectories
subdir('compat')
subdir('src')
