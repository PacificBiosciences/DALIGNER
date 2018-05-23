project(
  'daligner',
  'c',
  version : '0.0.1',
  default_options : [
    'buildtype=release',
    'warning_level=3',
    'c_std=gnu11',
    'b_ndebug=false'],
  license : 'BSD-3',
  meson_version : '>= 0.46.0')

############
# CXXFLAGS #
############

daligner_flags = []
cc = meson.get_compiler('c')
foreach cflag: [
  '-Wno-unused-result',
  '-Wno-pointer-arith',
  '-fno-strict-aliasing']
    if cc.has_argument(cflag)
      daligner_flags += cflag
    endif
endforeach

################
# dependencies #
################

# libm
daligner_m_dep = cc.find_library('m', required : false)

# threads
daligner_thread_dep = dependency('threads', required : true)

# dazzdb
daligner_dazzdb_dep = dependency('dazzdb', fallback : ['dazzdb', 'dazzdb_dep'])

daligner_deps = [daligner_m_dep, daligner_thread_dep, daligner_dazzdb_dep]

############
# binaries #
############

# install library if
# - either running as a proper project
# - or using shared libraries
daligner_lib_install = (not meson.is_subproject()) or (get_option('default_library') == 'shared')

daligner_lib = library(
  'daligner',
  files([
    'align.c']),
  # use boost SONAME practice:
  #   cause ld startup issues before
  #   you even have the chance of running
  #   into ABI issues.
  soversion : meson.project_version(),
  version : meson.project_version(),
  install : daligner_lib_install,
  dependencies : daligner_deps,
  c_args : daligner_flags)

daligner_exes = [
  ['daligner', files(['filter.c'])],
  ['HPC.daligner', []],
  ['LAsort', []],
  ['LAmerge', []],
  ['LAsplit', []],
  ['LAcat', []],
  ['LAshow', []],
  ['LAdump', []],
  ['LAcheck', []],
  ['LAindex', []],
  ['daligner_p', files(['filter_p.c'])],
  ['LA4Falcon', files(['DBX.c'])],
  ['LA4Ice', []],
  ['DB2Falcon', []]]

foreach i : daligner_exes
  executable(
    i[0],
    files([i[0] + '.c']) + i[1],
    dependencies : daligner_deps,
    install : (not meson.is_subproject()),
    c_args : daligner_flags,
    link_with : daligner_lib)
endforeach

###################
# dependency info #
###################

if not meson.is_subproject()
  import('pkgconfig').generate(
    libraries : daligner_lib,
    version : meson.project_version(),
    name : 'daligner',
    filebase : 'daligner',
    subdirs : 'daligner',
    description : 'Daligner library')

  install_headers(
    files([
      'align.h']),
    subdir : 'daligner')
endif

daligner_dep = declare_dependency(
  include_directories : include_directories('.'),
  link_with : daligner_lib,
  version : meson.project_version())
