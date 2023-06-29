wc_prog = executable(
  'wc',
  [ 'wc.c' ],
  include_directories : inc,
  dependencies : [ ],
  link_with : [ libcompat ],
  install : true,
)
install_man('wc.1')
