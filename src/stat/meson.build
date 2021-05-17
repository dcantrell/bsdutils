stat_prog = executable(
    'stat',
    [ 'stat.c' ],
    include_directories : [ inc, ],
    link_with : [ libcompat, ],
    install : true,
)

install_man('stat.1')
