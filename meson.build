project('bsdutils',
        [ 'c', 'cpp' ],
        version : '13.1',
        default_options : [
            'c_std=c99',
            'warning_level=2',
            'werror=false',
            'buildtype=debugoptimized'
        ],
        license : 'BSD-3-Clause')

# Start with compilers for C and C++
cc = meson.get_compiler('c')
cpp = meson.get_compiler('cpp')

# FreeBSD code sometimes ignores things
add_global_arguments([ '-Wno-unused-result' ], language : [ 'c', 'cpp' ])

# Avoid a pointless warning in some programs
if cc.has_argument('-Wstring-plus-int')
    add_global_arguments([ '-Wno-string-plus-int' ], language : [ 'c' ])
endif

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

if cc.has_function('strlcpy')
   add_global_arguments('-DHAVE_STRLCPY', language : [ 'c', 'cpp' ])
endif

if cc.has_function('strlcat')
   add_global_arguments('-DHAVE_STRLCAT', language : [ 'c', 'cpp' ])
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
if not libtinfo.found() and get_option('color_ls')
    error('a terminfo library is needed')
endif

# bc(1) needs libedit
libedit = dependency('libedit', required : get_option('libedit'))

# dc(1), install(1) and sort(1) need libcrypto
libcrypto = dependency('libcrypto', required : get_option('libcrypto'))

# seq(1) needs libm
libm = cc.find_library('m', required : true)

# df(1) needs libxo
libxo = dependency('libxo', required : true)

# needed by a few utils; provided by glibc, but not by e.g. musl

fts_dirs = []
rpmatch_dirs = []

if get_option('fts_path') != ''
    fts_dirs += get_option('fts_path')
endif

if get_option('rpmatch_path') != ''
    rpmatch_dirs += get_option('rpmatch_path')
endif

libfts = dependency('', required: false, static : get_option('static_fts'))
if not cc.has_function('fts_open', prefix: '#include <fts.h>')
    libfts = cc.find_library('fts', static : get_option('static_fts'), dirs : fts_dirs)
endif
librpmatch = cc.find_library('rpmatch',
    required : false, static : get_option('static_rpmatch'), dirs : rpmatch_dirs
)

# sort needs pthreads
libpthread = dependency('threads')

# Header files for libcompat
inc = include_directories('include')

# Symlink installation script
install_link = meson.current_source_dir() / 'utils/install-link.sh'

# Include all of the relevant subdirectories
subdir('compat')
subdir('src')
