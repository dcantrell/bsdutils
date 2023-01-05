stat_prog = executable(
    'stat',
    [ 'stat.c' ],
    include_directories : [ inc, ],
    link_with : [ libcompat, ],
    install : true,
)

install_man('stat.1b')

meson.add_install_script(install_link, 'stat', 'readlink', get_option('bindir'))
meson.add_install_script(
    install_link, 'stat.1b', 'readlink.1',
    join_paths(get_option('mandir'), 'man1')
)
