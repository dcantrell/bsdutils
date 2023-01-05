who_prog = executable(
    'who',
    [ 'who.c' ],
    include_directories : [ inc, ],
    link_with : [ libcompat ],
    install : true,
)

install_man('who.1')
