add_project_arguments('-Wno-sign-compare', '-Wno-maybe-uninitialized', '-Wno-format-truncation', language : 'c')

libcompat_sources = [
    'setmode.c',
    'strlcat.c',
    'strlcpy.c',
    'strtonum.c',
    'strmode.c',
    'pwcache.c',
    'ohash.c',
    'fmt_scaled.c',
    'getbsize.c',
    'devname.c',
    'merge.c',
    'heapsort.c',
    'recallocarray.c',
]

libcompat = static_library(
    'compat',
    libcompat_sources,
    include_directories : inc,
)
