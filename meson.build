# vim:set et sw=2 ts=2 tw=79 fdm=marker:
project('preload', 'c',
  version : '0.1.5',
  meson_version : '>=0.59.1',
  license : 'GPL-2.0-only',
  default_options : [
    'warning_level=3',
    'buildtype=debugoptimized',
    'prefix=/usr',
  ],
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

add_project_arguments(macros, language: 'c')
# 1}}} #

# config.h data {{{1 #
conf = configuration_data()

conf.set_quoted('PACKAGE', meson.project_name())
conf.set_quoted('LOGDIR', get_option('localstatedir') / 'log')
conf.set_quoted('SYSCONFDIR', get_option('sysconfdir'))
conf.set_quoted('SHAREDSTATEDIR', get_option('sharedstatedir'))
conf.set_quoted('PACKAGE_VERSION', meson.project_version())
conf.set_quoted('PACKAGE_STRING',
  '@0@ @1@'.format(meson.project_name(), meson.project_version()),
)
conf.set_quoted('PACKAGE_NAME', meson.project_name())
conf.set_quoted('PACKAGE_BUGREPORT',
  'https://github.com/arunanshub/preload/issues')

configure_file(
  output : 'config.h',
  configuration : conf,
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

# Manpage generation and installation {{{1 #
help2man = find_program('help2man', required : false, disabler : true)

help2man.found() ? '' : warning('help2man not found. Not installing manpage')

section = 8

help2man_opts = [
  '--no-info',
  '--section=@0@'.format(section),
  '--name="Adaptive readahead daemon"',
]

custom_target(
  '@0@.@1@'.format(exe.name(), section),
  input : 'man' / '@0@.@1@.i'.format(exe.name(), section),
  output : '@0@.@1@'.format(exe.name(), section),
  build_by_default : true,
  command : [
    help2man,
    help2man_opts,
    '--include=@INPUT@',
    '--output=@OUTPUT@',
    exe,
  ],
  install : true,
  # using `install_man(...)` tries to search for the (nonexistent) manpage, but
  # since it is generated dynamically during build time, we have to manually
  # specify install dir.
  install_dir : get_option('mandir') / 'man@0@'.format(section),
)
# 1}}} #

# tests {{{1 #
testexe = find_program('runtests.sh')
env = {
  'APPNAME': exe.full_path(),
}

test(
  'With debug config',
  testexe,
  args : ['debug'],
  env : env,
)

test(
  'With normal config',
  testexe,
  args : ['normal'],
  env : env,
)
# }}}1 #
