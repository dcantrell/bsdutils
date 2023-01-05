date_prog = executable(
    'date',
    [ 'date.c',
      'vary.c',
    ],
    include_directories : inc,
    link_with : [ libcompat ],
    install : true,
)

install_man('date.1b')
