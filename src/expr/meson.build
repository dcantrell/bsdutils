expr_prog = executable(
    'expr',
    [ yacc.process('expr.y'), ],
    include_directories : inc,
    install : true,
)

install_man('expr.1')
