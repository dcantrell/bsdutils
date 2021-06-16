chown_prog = executable(
    'chown',
    [ 'chown.c' ],
    c_args : [ '-DUID_MAX=INT_MAX', '-DGID_MAX=INT_MAX' ],
    include_directories : inc,
    dependencies : [ libfts, ],
    install : true,
    install_dir : get_option('sbindir'),
)

# XXX: this should be a relative symlink to chown
chgrp_prog = executable(
    'chgrp',
    [ 'chown.c' ],
    c_args : [ '-DUID_MAX=INT_MAX', '-DGID_MAX=INT_MAX' ],
    include_directories : inc,
    dependencies : [ libfts, ],
    install : true,
)

install_man('chown.8')
install_man('chgrp.1')
