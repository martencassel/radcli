task :clone_adcli do
    sh "rm -rf ./adcli && git clone http://cgit.freedesktop.org/realmd/adcli/"
end

task :build_adcli => 'clone_adcli' do
    sh "cd ./adcli && ./autogen.sh --prefix=/usr --sysconfdir=/etc && make && mv ./library/.libs/libadcli.a ../ext/lib/"
    sh "rm -rf ./adcli"
end

task :default => :build_adcli

