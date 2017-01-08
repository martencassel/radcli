task :clone_adcli do
    sh "sudo yum -y groupinstall 'Development Tools' && sudo yum -y install automake autoconf xmlto xsltproc krb5-devel openldap-devel cyrus-sasl-devel"
    sh "rm -rf ./adcli && git clone http://cgit.freedesktop.org/realmd/adcli/"
end

task :build_adcli => 'clone_adcli' do
    sh "cd ./adcli && ./autogen.sh --prefix=/usr --sysconfdir=/etc && make && mv ./library/.libs/libadcli.a ../ext/lib/"
    sh "git add -f ./ext/lib/libadcli.a"
    sh "rm -rf ./adcli"
end

task :default => :build_adcli

