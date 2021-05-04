test_prog = executable(
    'xtest',
    [ 'test.c' ],
    install : true,
)

meson.add_install_script('install.sh', get_option('bindir'))
install_man('test.1')
