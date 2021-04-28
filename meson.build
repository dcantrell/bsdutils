project('bsdutils',
        'c',
        version : '1.0',
        default_options : [
            'c_std=c99',
            'warning_level=2',
            'buildtype=debugoptimized'
        ],
        license : 'ISC')

cc = meson.get_compiler('c')

# Enable glibc features we require
add_global_arguments('-D_GNU_SOURCE', language : 'c')

# Header files for libcompat
inc = include_directories('compat')

# Include all of the relevant subdirectories
subdir('compat')
