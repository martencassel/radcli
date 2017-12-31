require 'rubygems'

Gem::Specification.new do |spec|
    spec.name       = 'radcli'
    spec.version    = '1.0.0'
    spec.authors    = ['Mårten Cassel']
    spec.license    = 'Artistic-2.0'
    spec.email      = ['marten.cassel@gmail.com']
    spec.homepage   = 'http://github.com/martencassel/radcli'
    spec.summary    = 'A Ruby interface for the adcli library'
    spec.test_files = Dir['test/test*']
    spec.extensions = ['ext/radcli/extconf.rb']
    spec.files      = `git ls-files`.split("\n").reject { |f| f.include?('git') }

    spec.extra_rdoc_files  = ['README.md', 'CHANGES', 'MANIFEST'] + Dir['ext/radcli/*.c']

    spec.add_dependency('rake-compiler')

    spec.add_development_dependency('test-unit', '>= 2.1.0')
    
    spec.description = <<-EOF
      The radcli library provides a Ruby interface for performing actions on 
      a Active Directory domain using the realmd/adcli tool library.
    EOF
end

