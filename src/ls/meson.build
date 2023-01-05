ls_cargs = []
ls_deps = [ libfts, ]

if get_option('color_ls')
    ls_cargs += [ '-DCOLORLS' ]
    ls_deps += [ libtinfo ]
endif

ls_prog = executable(
    'ls',
    [ 'cmp.c',
      'ls.c',
      'print.c',
      'util.c',
    ],
    c_args : ls_cargs,
    include_directories : inc,
    link_with : [ libcompat ],
    dependencies : ls_deps,
    install : true,
)

install_man('ls.1b')
