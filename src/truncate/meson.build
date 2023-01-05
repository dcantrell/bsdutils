truncate_prog = executable(
    'truncate',
    [ 'truncate.c' ],
    include_directories : inc,
    link_with : [ libcompat ],
    install : true,
)

install_man('truncate.1b')
