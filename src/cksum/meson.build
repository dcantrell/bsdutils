srcs = [ 'cksum.c', 'crc.c', 'print.c', 'sum1.c', 'sum2.c', 'crc32.c' ]

cksum_prog = executable(
    'cksum',
    srcs,
    c_args : [ '-Duint32_t=u_int32_t' ],
    include_directories : inc,
    install : true,
)

meson.add_install_script(install_link, 'cksum', 'sum', get_option('bindir'))

install_man('cksum.1')
install_man('sum.1')
