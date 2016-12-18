require "mkmf"

LIBDIR     = RbConfig::CONFIG['libdir']
INCLUDEDIR = RbConfig::CONFIG['includedir']
HEADER_DIRS = [INCLUDEDIR, File.expand_path(File.join(File.dirname(__FILE__), "ext/radcli"))]
LIB_DIRS = [LIBDIR, File.expand_path(File.join(File.dirname(__FILE__), "../lib"))]
libs = ['-ladcli', '-lldap', '-lkrb5', '-lsasl2', '-lgssapi_krb5']

dir_config('radcli', HEADER_DIRS, LIB_DIRS)

libs.each do |lib|
  $LOCAL_LIBS << "#{lib} "
end

create_makefile('radcli')

