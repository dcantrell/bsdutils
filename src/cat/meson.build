cat_prog = executable(
    'cat',
    [ 'cat.c' ],
    include_directories : inc,
    c_args : '-DNO_UDOM_SUPPORT',
    install : true,
)

install_man('cat.1')
