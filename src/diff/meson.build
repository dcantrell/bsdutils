diff_prog = executable(
    'diff',
    [ 'diff.c',
      'diffdir.c',
      'diffreg.c',
      'xmalloc.c',
      'pr.c',
    ],
    include_directories : inc,
    link_with : [ libcompat ],
    install : true,
)

install_man('diff.1')

