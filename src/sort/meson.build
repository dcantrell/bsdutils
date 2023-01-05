sort_cargs = [ '-DWITHOUT_NLS', '-DSORT_THREADS', ]

if not libcrypto.found()
    sort_cargs += [ '-DWITHOUT_LIBCRYPTO' ]
endif

sort_prog = executable(
    'sort',
    [
        'bwstring.c', 'coll.c', 'file.c', 'mem.c',
        'radixsort.c', 'sort.c', 'vsort.c',
    ],
    include_directories : [ inc, ],
    dependencies : [ libcrypto, libpthread, ],
    link_with : [ libcompat, ],
    c_args : sort_cargs,
    install : true,
)

install_man('sort.1')
