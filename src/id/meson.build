id_prog = executable(
    'id',
    [ 'id.c' ],
    include_directories : inc,
    install : true,
)

meson.add_install_script(install_link, 'id', 'groups', get_option('bindir'))
meson.add_install_script(install_link, 'id', 'whoami', get_option('bindir'))

install_man('id.1')
install_man('groups.1')
install_man('whoami.1')
