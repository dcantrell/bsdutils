rm_prog = executable(
    'rm',
    [ 'rm.c' ],
    include_directories : [ inc, ],
    dependencies : [ libfts, ],
    link_with : [ libcompat, ],
    install : true,
)

install_man('rm.1')

meson.add_install_script(install_link, 'rm', 'unlink', get_option('bindir'))
meson.add_install_script(
    install_link, 'rm.1', 'unlink.1', join_paths(get_option('mandir'), 'man1')
)
