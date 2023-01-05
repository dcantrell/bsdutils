which_prog = executable(
    'which',
    [ 'which.c' ],
    include_directories : [ inc, ],
    install : true,
    install_dir : get_option('bindir'),
)

install_man('which.1b')
