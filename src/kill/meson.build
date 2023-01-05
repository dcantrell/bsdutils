kill_prog = executable(
    'kill',
    [ 'kill.c' ],
    include_directories : [ inc, ],
    link_with : [ libcompat, ],
    install : true,
)

install_man('kill.1b')
