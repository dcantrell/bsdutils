cp_prog = executable(
    'cp',
    [ 'cp.c',
      'utils.c',
    ],
    dependencies : [ fts, ],
    include_directories : inc,
    install : true,
)

install_man('cp.1')
