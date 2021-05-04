dd_prog = executable(
    'dd',
    [ 'args.c',
      'conv.c',
      'conv_tab.c',
      'dd.c',
      'misc.c',
      'position.c',
    ],
    include_directories : inc,
    link_with : [ libcompat ],
    install : true,
)

install_man('dd.1')
