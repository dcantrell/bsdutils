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
      '-D__FBSDID(x)=',
      '-D__dead2=',
      '-D__unused=__attribute__((unused))',
      '-D__printf0like(x, y)=',
      '-D__SCCSID(x)=',
    ],
    language : [ 'c', 'cpp' ]
)

# Build everything with _GNU_SOURCE enabled
add_global_arguments('-D_GNU_SOURCE', language : [ 'c', 'cpp' ])

# ls(1) needs the terminfo library
tinfo = dependency('tinfo', required : true)

# bc(1) needs libedit
libedit = dependency('libedit', required : true)

# dc(1) and install(1) need libcrypto
libcrypto = dependency('libcrypto', required : true)

# seq(1) needs libm
libm = cc.find_library('m', required : true)

# Header files for libcompat
inc = include_directories('include')

# Include all of the relevant subdirectories
subdir('compat')
subdir('src')
