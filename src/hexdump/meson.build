hexdump_prog = executable(
    'hexdump',
    [ 'conv.c',
      'display.c',
      'hexdump.c',
      'hexsyntax.c',
      'odsyntax.c',
      'parse.c',
    ],
    include_directories : [ inc, ],
    link_with : [ libcompat ],
    install : true,
)

install_man('od.1b')
install_man('hexdump.1b')

meson.add_install_script(install_link, 'hexdump', 'od', get_option('bindir'))
meson.add_install_script(install_link, 'hexdump', 'hd', get_option('bindir'))
meson.add_install_script(
    install_link, 'hexdump.1b', 'hd.1', join_paths(get_option('mandir'), 'man1')
)
