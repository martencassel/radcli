#!/bin/sh
yum -y groupinstall 'Development Tools' && sudo yum -y install automake autoconf xmlto xsltproc krb5-devel openldap-devel cyrus-sasl-devel
rm -rf ./adcli && git clone http://cgit.freedesktop.org/realmd/adcli/
cd ./adcli && ./autogen.sh --prefix=/usr --sysconfdir=/etc && make && mv ./library/.libs/libadcli.a ../ext/lib/
git add -f ./ext/lib/libadcli.a
rm -rf ./adcli
