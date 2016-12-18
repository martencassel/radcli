require 'rubygems'

Gem::Specification.new do |spec|
    spec.name       = 'radcli'
    spec.version    = '0.0.1'
    spec.authors    = ['Mårten Cassel']
    spec.license    = 'Artistic 2.0'
    spec.email      = ['marten.cassel@gmail.com']
    spec.homepage   = 'http://github.com/martencassel/radcli'
    spec.summary    = 'A Ruby interface for the adcli library'
    spec.test_files = Dir['test/test*']
    spec.extensions = ['ext/radcli/extconf.rb']
    spec.files      = `git ls-files`.split("\n").reject { |f| f.include?('git') }
    
    spec.extra_rdoc_files  = ['README.md', 'CHANGES', 'MANIFEST', 'LICENSE'] + Dir['ext/radcli/*.c']
    
    spec.add_dependency('rake-compiler') 

end

