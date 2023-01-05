env_prog = executable(
    'env',
    [ 'env.c',
      'envopts.c',
    ],
    include_directories : inc,
    link_with : [ libcompat ],
    install : true,
)

install_man('env.1')
