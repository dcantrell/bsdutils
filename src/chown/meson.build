chown_prog = executable(
    'chown',
    [ 'chown.c' ],
    c_args : [ '-DUID_MAX=INT_MAX', '-DGID_MAX=INT_MAX' ],
    include_directories : inc,
    dependencies : [ libfts, ],
    install : true,
    install_dir : get_option('sbindir'),
)

meson.add_install_script(install_link, 'chown', 'chgrp', get_option('bindir'))

install_man('chown.8b')
install_man('chgrp.1b')
