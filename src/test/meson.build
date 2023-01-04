test_prog = executable(
    'xtest',
    [ 'test.c' ],
    include_directories : inc
)

install_man('test.1')
meson.add_install_script('install.sh', get_option('bindir'))
