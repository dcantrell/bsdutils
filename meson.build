project('bsdutils',
        'c',
        version : '1.0',
        default_options : [
            'c_std=c99',
            'warning_level=2',
            'buildtype=debugoptimized'
        ],
        license : 'BSD-3-Clause')

cc = meson.get_compiler('c')
#cpp = meson.get_compiler('cpp')

# Define some macros to eliminate some FreeBSD-specifics in the code
add_global_arguments('-Dlint', language : 'c')
add_global_arguments('-D__FBSDID(x)=', language : 'c')
add_global_arguments('-D__dead2=', language : 'c')
add_global_arguments('-D__unused=__attribute__((unused))', language : 'c')
add_global_arguments('-D__printf0like(x, y)=', language : 'c')
add_global_arguments('-D__SCCSID(x)=', language : 'c')

# Build everything with _GNU_SOURCE enabled
add_global_arguments('-D_GNU_SOURCE', language : 'c')

# Header files for libcompat
inc = include_directories('include')

# Include all of the relevant subdirectories
subdir('compat')
subdir('src')
