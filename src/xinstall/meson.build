xinstall_prog = executable(
    'xinstall',
    [ 'xinstall.c', ],
    include_directories : [ inc, ],
    link_with : [ libcompat, ],
    dependencies : [ libcrypto, ],
)

meson.add_install_script('install.sh', get_option('bindir'))
install_man('install.1b')
