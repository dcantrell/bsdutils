bc_prog = executable(
    'bc',
    [ yacc.process('bc.y'),
      lex.process('scan.l'),
      'tty.c',
    ],
    dependencies : [ libedit ],
    install : true,
)

install_man('bc.1')
install_data('bc.library',
             install_dir : get_option('datadir') / 'misc')
