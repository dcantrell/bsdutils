rm_prog = executable(
    'rm',
    [ 'rm.c' ],
    include_directories : [ inc, ],
    dependencies : [ fts, ],
    link_with : [ libcompat, ],
    install : true,
)

install_man('rm.1')
