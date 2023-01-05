# expr relies on signed integer wrapping
extra_args = [ '-fwrapv' ]

expr_prog = executable(
    'expr',
    [ yacc.process('expr.y'), ],
    include_directories : inc,
    c_args : extra_args,
    install : true,
)

install_man('expr.1b')
