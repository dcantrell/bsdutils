ls_prog = executable(
    'ls',
    [ 'cmp.c',
      'ls.c',
      'print.c',
      'util.c',
    ],
    c_args : [ '-DCOLORLS' ],
    include_directories : inc,
    link_with : [ libcompat ],
    dependencies : [ tinfo ],
    install : true,
)

install_man('ls.1')
