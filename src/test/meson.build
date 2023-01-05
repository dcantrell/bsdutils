test_prog = executable(
    'xtest',
    [ 'test.c' ],
    include_directories : inc,
)

meson.add_install_script('install.sh', get_option('bindir'))

install_man('test.1')

meson.add_install_script(install_link, 'test', '[', get_option('bindir'))
meson.add_install_script(
    install_link, 'test.1', '[.1', join_paths(get_option('mandir'), 'man1')
)
