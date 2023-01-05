tail_prog = executable(
    'tail',
    [ 'forward.c',
      'misc.c',
      'read.c',
      'reverse.c',
      'tail.c',
    ],
    include_directories : [ inc, ],
    install : true,
)

install_man('tail.1b')
