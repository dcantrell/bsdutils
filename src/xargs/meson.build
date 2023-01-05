xargs_prog = executable(
    'xargs',
    [ 'strnsubst.c',
      'xargs.c',
    ],
    include_directories : [ inc, ],
    link_with : [ libcompat ],
    install : true,
)

install_man('xargs.1b')
