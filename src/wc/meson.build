wc_prog = executable(
    'wc',
    [ 'wc.c' ],
    include_directories : [ inc, ],
    dependencies : [ libxo ],
    install : true,
)

install_man('wc.1b')
