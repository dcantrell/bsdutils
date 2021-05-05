dc_prog = executable(
    'dc',
    [ 'dc.c',
      'bcode.c',
      'inout.c',
      'mem.c',
      'stack.c',
    ],
    dependencies : [ libcrypto, ],
    install : true,
)

install_man('dc.1')
