sync_prog = executable(
    'sync',
    [ 'sync.c' ],
    include_directories : inc,
    install : true,
    install_dir : get_option('sbindir'),
)

install_man('sync.8b')
