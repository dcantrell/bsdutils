ln_prog = executable(
    'ln',
    [ 'ln.c' ],
    include_directories : inc,
    install : true,
)

install_man('ln.1')
install_man('symlink.7')

meson.add_install_script(install_link, 'ln', 'link', get_option('bindir'))
meson.add_install_script(
    install_link, 'ln.1', 'link.1', join_paths(get_option('mandir'), 'man1')
)
