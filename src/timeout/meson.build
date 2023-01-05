timeout_prog = executable(
    'timeout',
    [ 'timeout.c' ],
    include_directories : inc,
    link_with : [ libcompat, ],
    install : true,
)

install_man('timeout.1b')
