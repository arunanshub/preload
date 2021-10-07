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

# configuration data {{{1 #
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

dependencies = [
  dependency('glib-2.0'),
  cc.find_library('m', required : false), # add math library
]

include = include_directories('include')
subdir('src')

executable(
  'preload',
  src,
  include_directories : include,
  dependencies : dependencies,
  install : true,
)
