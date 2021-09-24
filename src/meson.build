src = [
  'cmdline.c',
  'conf.c',
  'log.c',
  'preload.c',
  'proc.c',
  'prophet.c',
  'readahead.c',
  'spy.c',
  'state.c',
]

configure_file(
  output : 'config.h',
  configuration : conf_data,
)

executable(
  'preload',
  src,
  include_directories : include,
  dependencies : dependencies,
  install : true,
)
