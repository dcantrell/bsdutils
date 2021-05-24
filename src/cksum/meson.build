srcs = [ 'cksum.c', 'crc.c', 'print.c', 'sum1.c', 'sum2.c', 'crc32.c' ]

cksum_prog = executable(
    'cksum',
    srcs,
    c_args : [ '-Duint32_t=u_int32_t' ],
    include_directories : inc,
    install : true,
)

# XXX: this should be a relative symlink to cksum
sum_prog = executable(
    'sum',
    srcs,
    c_args : [ '-Duint32_t=u_int32_t' ],
    include_directories : inc,
    install : true,
)

install_man('cksum.1')
install_man('sum.1')
