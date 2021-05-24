dc_prog = executable(
    'dc',
    [ 'dc.c',
      'bcode.c',
      'inout.c',
      'mem.c',
      'stack.c',
    ],
    include_directories : inc,
    dependencies : [ libcrypto, ],
    install : true,
)

install_man('dc.1')
