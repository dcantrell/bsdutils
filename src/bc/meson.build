bc_prog = executable(
    'bc',
    [ yacc.process('bc.y'),
      lex.process('scan.l'),
      'tty.c',
    ],
    include_directories : inc,
    link_with : [ libcompat ],
    dependencies : [ libedit ],
    install : true,
)

install_man('bc.1b')
install_data('bc.library',
             install_dir : get_option('datadir') / 'misc')
