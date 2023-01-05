cp_prog = executable(
    'cp',
    [ 'cp.c',
      'utils.c',
    ],
    dependencies : [ libfts, ],
    include_directories : inc,
    link_with : [ libcompat ],
    install : true,
)

install_man('cp.1')
