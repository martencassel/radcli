#!/bin/sh

dnf -y update
dnf -y groupinstall 'Development Tools'
dnf -y install libtool automake autoconf xmlto xsltproc krb5-devel openldap-devel cyrus-sasl-devel

rm -rf ./adcli && git clone https://gitlab.freedesktop.org/realmd/adcli.git
cd ./adcli 
autoreconf -i
./autogen.sh --prefix=/usr --sysconfdir=/etc
make 

cp ./library/.libs/libadcli.a /buildroot/

#mv ./library/.libs/libadcli.a ../ext/lib/
#git add -f ./ext/lib/libadcli.a
#rm -rf ./adcli
