# vim:set et sw=2 ts=4 tw=80 fdm=marker:
project('preload', 'c',
  version : '0.1.3',
  default_options : ['warning_level=3'])

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

# project arguments {{{1 #
add_project_arguments(
  [
    '-D_GNU_SOURCE',
    '-DHAVE_STRINGIZE',
    '-DHAVE_SYS_STAT_H',
    '-DHAVE_SYS_TYPES_H',
    '-DHAVE_CONFIG_H',
  ],
  language: 'c',
)
# 1}}} #

cc = meson.get_compiler('c')

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
