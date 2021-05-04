chmod_prog = executable(
    'chmod',
    [ 'chmod.c' ],
    include_directories : inc,
    link_with : [ libcompat ],
    install : true,
)

install_man('chmod.1')
