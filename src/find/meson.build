find_prog = executable(
    'find',
    [ 'find.c',
      'function.c',
      yacc.process('getdate.y'),
      'ls.c',
      'main.c',
      'misc.c',
      'operator.c',
      'option.c',
    ],
    c_args : [ '-DQUAD_MAX=LONG_MAX',
               '-DMAXLOGNAME=LOGIN_NAME_MAX', ],
    include_directories : inc,
    link_with : [ libcompat ],
    install : true,
)

install_man('find.1')
