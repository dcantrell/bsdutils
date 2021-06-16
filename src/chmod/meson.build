chmod_prog = executable(
    'chmod',
    [ 'chmod.c' ],
    include_directories : inc,
    dependencies : [ libfts, ],
    link_with : [ libcompat ],
    install : true,
)

install_man('chmod.1')
