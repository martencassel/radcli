require "bundler/gem_tasks"
require "rubygems/package_task"
require "rake/extensiontask"
require "rspec/core/rake_task"
require "rake/clean"
require "rake/testtask"

CLEAN.include(
    "ext/radcli/*.o",
    "ext/radcli/*.bundle"
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

RSpec::Core::RakeTask.new(:spec)

namespace 'test' do
  Rake::TestTask.new('all') do |t|
    task:all => [:clean, :compile]
    t.libs << 'ext/radcli'
    t.warning = true
    t.verbose = true
  end
end

task :build   => [:clean, :compile]

task :default => [:build, :spec]

task :test => ['test:all']

