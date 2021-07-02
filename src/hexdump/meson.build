hexdump_prog = executable(
    'hexdump',
    [ 'conv.c', 'display.c', 'hexdump.c', 'hexsyntax.c', 'odsyntax.c', 'parse.c' ],
    include_directories : [ inc, ],
    install : true,
)

install_man('od.1')
install_man('hexdump.1')

meson.add_install_script(install_link, 'hexdump', 'od', get_option('bindir'))
meson.add_install_script(install_link, 'hexdump', 'hd', get_option('bindir'))
meson.add_install_script(install_link, 'hexdump.1', 'hd.1', get_option('mandir') + '/man1')
