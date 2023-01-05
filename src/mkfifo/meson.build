mkfifo_prog = executable(
    'mkfifo',
    [ 'mkfifo.c' ],
    include_directories : [ inc, ],
    link_with : [ libcompat, ],
    install : true,
    install_dir : get_option('bindir'),
)

install_man('mkfifo.1b')
