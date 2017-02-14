require 'rake'
require 'rake/testtask'
require 'rake/extensiontask'
require 'rake/clean'
require 'rbconfig'
require 'rubygems/package'
require 'bundler/gem_tasks'

CLEAN.include(
    "ext/radcli/*.o",
    "ext/radcli/*.bundle",
    "**/tmp"
)

CLOBBER.include(
    "ext/radcli/Makefile",
    "pkg"
)

BUILD_DIR = 'build'

def gem_spec
    @gem_spec ||= Gem::Specification.load('radcli.gemspec')
end

Gem::PackageTask.new(gem_spec) do |pkg|
    pkg.need_zip = true
    pkg.need_tar = true
end

Rake::ExtensionTask.new("radcli", gem_spec) do |ext|
     ext.ext_dir = './ext/radcli' 
     ext.lib_dir = './ext/lib'
     ext.config_script = "extconf.rb"
end

namespace 'test' do

  Rake::TestTask.new('all') do |t|
    task :all => [:clean, :compile]
    t.libs << 'ext/radcli' 
    t.warning = true
    t.verbose = true
  end

  Rake::TestTask.new('adconn') do |t|
    task :context => [:clean, :compile]
    t.libs << 'ext' 
    t.test_files = FileList['test/test_radconn.rb']
    t.warning = true
    t.verbose = true
  end

  Rake::TestTask.new('adenroll') do |t|
    task :context => [:clean, :compile]
    t.libs << 'ext'
    t.test_files = FileList['test/test_radenroll.rb']
    t.warning = true
    t.verbose = true
  end
end

task :build   => [:clean, :compile]

task :default => ['test:all']
