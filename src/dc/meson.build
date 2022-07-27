dc_prog = executable(
    'dc',
    [ 'dc.c',
      'bcode.c',
      'inout.c',
      'mem.c',
      'stack.c',
    ],
    include_directories : inc,
    link_with : [ libcompat ],
    dependencies : [ libcrypto, ],
    install : true,
)

install_man('dc.1')
