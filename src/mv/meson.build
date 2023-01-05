mv_prog = executable(
    'mv',
    [ 'mv.c' ],
    c_args : [ '-D_PATH_CP="/bin/cp"',
               '-D_PATH_RM="/bin/rm"', ],
    include_directories : inc,
    link_with : [ libcompat ],
    install : true,
)

install_man('mv.1')
