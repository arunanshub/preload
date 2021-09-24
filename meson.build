project('preload-meson', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

src = [
  'cmdline.c',
  'cmdline.h',
  'common.h',
  'conf.c',
  'conf.h',
  'confkeys.h',
  # 'gen.preload.conf.sh',
  'log.c',
  'log.h',
  # 'Makefile.am',
  # 'Makefile.in',
  # 'preload.8',
  # 'preload.8.i',
  'preload.c',
  # 'preload.conf.in',
  'preload.h',
  'proc.c',
  'proc.h',
  'prophet.c',
  'prophet.h',
  'readahead.c',
  'readahead.h',
  # 'runtests.sh',
  'spy.c',
  'spy.h',
  'state.c',
  'state.h',
]

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : true)

executable(
  'preload',
  src,
  dependencies : [
    dependency('glib-2.0'),
    m_dep,
  ],
  c_args : [
    '-DHAVE_STRINGIZE',
    '-DVERSION=1',
    '-DPACKAGE="preload"',
    '-DLOGDIR=""',
    '-DSYSCONFDIR=""',
    '-DPKGLOCALSTATEDIR=""',
    '-DPACKAGE_STRING="testing"',
    '-DPACKAGE_NAME="testing"',
    '-DPACKAGE_BUGREPORT="testing"',
  ],
  install : true,
)
