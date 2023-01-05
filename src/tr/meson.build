tr_prog = executable(
    'tr',
    [ 'tr.c', 'cmap.c', 'cset.c', 'str.c' ],
    include_directories : [ inc, ],
    link_with : [ libcompat, ],
    install : true,
)

install_man('tr.1b')
