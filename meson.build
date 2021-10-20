# vim:set et sw=2 ts=4 tw=80 fdm=marker:
project('preload', 'c',
  version : '0.1.4',
  meson_version : '>=0.59.1',
  license : 'GPL-2.0-only',
  default_options : ['warning_level=3'],
)

cc = meson.get_compiler('c')

# Stringize check {{{1 #
if not cc.compiles('#define FOO(x) #x', name : 'stringize check')
  error('stringizing not supported by this compiler')
endif
# 1}}} #

# project arguments {{{1 #
macros = [
  '-D_GNU_SOURCE',
  '-DHAVE_CONFIG_H',
]

if cc.has_header('sys/stat.h')
  macros += '-DHAVE_SYS_STAT_H'
else
  error('"sys/stat.h" is absent')
endif

foreach header : ['sys/types.h', 'linux/fs.h']
  if cc.has_header(header)
    macros += '-DHAVE_' + header.to_upper().underscorify()
  endif
endforeach

add_project_arguments(
  macros,
  language: 'c',
)
# 1}}} #

# config.h data {{{1 #
PACKAGE_STRING = '"@0@ @1@"'.format(
  meson.project_name(),
  meson.project_version()
)

conf_data = configuration_data({
  'PACKAGE'           : '"@0@"'.format(meson.project_name()),
  'LOGDIR'            : '"/var/log"',
  'SYSCONFDIR'        : '"/etc"',
  'PKGLOCALSTATEDIR'  : '"/var/lib"',
  'PACKAGE_VERSION'   : '"@0@"'.format(meson.project_version()),
  'PACKAGE_STRING'    : PACKAGE_STRING,
  'PACKAGE_NAME'      : '"preload"',
  'PACKAGE_BUGREPORT' : '"https://github.com/arunanshub/preload/issues"',
})

configure_file(
  output : 'config.h',
  configuration : conf_data,
)
# 1}}} #

# preload.conf data {{{1 #
conf_data = configuration_data({
  'DEFAULT_CYCLE': 1,
  'DEFAULT_USECORRELATION' : 'true',
  'DEFAULT_MINSIZE': 2000000,
  'DEFAULT_MEMTOTAL' : -10,
  'DEFAULT_MEMFREE' : 50,
  'DEFAULT_MEMCACHED' : 0,
  'DEFAULT_DOSCAN' : 'true',
  'DEFAULT_DOPREDICT' : 'true',
  'DEFAULT_AUTOSAVE' : 3600,
  'DEFAULT_MAXPROCS' : 30,
  'DEFAULT_SORTSTRATEGY' : 3,
})

configure_file(
  output : 'preload.conf',
  input : 'preload.conf.in',
  configuration : conf_data,
  install : true,
  install_dir : get_option('sysconfdir'),
)
# 1}}} #

dependencies = [
  dependency('glib-2.0'),
  cc.find_library('m', required : false), # add math library
]

include = include_directories('include')
subdir('src')

exe = executable(
  'preload',
  src,
  include_directories : include,
  dependencies : dependencies,
  install : true,
)
#
# test('preload with debug config', exe, args : [
#   '-c preload.conf -s \'\' -d',
#   ],
# )
#
# test('preload with normal config', exe, args : [
#   '-c preload.conf -s \'\' -l \'\' -f',
#   ],
# )
