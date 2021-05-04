project('bsdutils',
        [ 'c', 'cpp' ],
        version : '1.0',
        default_options : [
            'c_std=c99',
            'warning_level=2',
            'buildtype=debugoptimized'
        ],
        license : 'BSD-3-Clause')

cc = meson.get_compiler('c')
cpp = meson.get_compiler('cpp')

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

# Header files for libcompat
inc = include_directories('include')

# Include all of the relevant subdirectories
subdir('compat')
subdir('src')
