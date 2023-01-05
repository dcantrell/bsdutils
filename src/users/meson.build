extra_args = [ '-fno-rtti' ]

users_prog = executable(
    'users',
    [ 'users.cc' ],
    include_directories : inc,
    cpp_args : extra_args,
    install : true,
)

install_man('users.1b')
