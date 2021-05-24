chroot_prog = executable(
    'chroot',
    [ 'chroot.c' ],
    include_directories : inc,
    install : true,
    install_dir : get_option('sbindir'),
)

install_man('chroot.8')
