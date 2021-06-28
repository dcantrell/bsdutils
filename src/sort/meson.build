sort_prog = executable(
    'sort',
    [
        'bwstring.c', 'coll.c', 'file.c', 'mem.c',
        'radixsort.c', 'sort.c', 'vsort.c',
    ],
    include_directories : [ inc, ],
    dependencies : [ libcrypto, libpthread, ],
    link_with : [ libcompat, ],
    c_args : [ '-DWITHOUT_NLS', '-DSORT_THREADS' ],
    install : true,
)

#install_man('sort.1')
