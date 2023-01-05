du_prog = executable(
    'du',
    [ 'du.c' ],
    include_directories : [ inc, ],
    dependencies : [ libfts, ],
    link_with : [ libcompat, ],
    install : true,
)

install_man('du.1')
