ln_prog = executable(
    'ln',
    [ 'ln.c' ],
    include_directories : inc,
    link_with : [ libcompat ],
    install : true,
)

install_man('ln.1b')
install_man('symlink.7b')

meson.add_install_script(install_link, 'ln', 'link', get_option('bindir'))
meson.add_install_script(
    install_link, 'ln.1b', 'link.1', join_paths(get_option('mandir'), 'man1')
)
