id_prog = executable(
    'id',
    [ 'id.c' ],
    include_directories : inc,
    install : true,
)

# XXX: this should be a relative symlink to id
groups_prog = executable(
    'groups',
    [ 'id.c' ],
    include_directories : inc,
    install : true,
)

# XXX: this should be a relative symlink to id
whoami_prog = executable(
    'whoami',
    [ 'id.c' ],
    include_directories : inc,
    install : true,
)

install_man('id.1')
install_man('groups.1')
install_man('whoami.1')
