# Description
The radcli library provides a Ruby interface for performing actions on a Active Directory domain using the realmd/adcli tool.
(adcli: https://www.freedesktop.org/software/realmd/adcli/devel-building.html)

# Installation


### Prerequisites (Ubuntu)
```
sudo apt-get install ruby gem ruby-dev
sudo gem install rake bundler rakecompiler rspec
sudo apt-get install automake autoconf xmlto xsltproc libkrb5-dev libldap2-dev libsasl2-dev
```

### Prerequisites (Fedora)
```
sudo yum ruby gem ruby-devel
gem install rake bundler rakecompiler rspec
sudo yum install automake autoconf xmlto xsltproc krb5-devel openldap-devel cyrus-sasl-devel
```

### Building
```
git clone https://github.com/martencassel/radcli
cd radcli
rake build
gem install pkg/radcli-1.0.0.gem
```

# Synposis

### Connect using username/password
```ruby
require 'radcli'

adconn = Adcli::AdConn.new("example.com")
adconn.set_domain_realm("EXAMPLE.COM")
adconn.set_domain_controller("dc.example.com")

adconn.set_login_user("Administrator")
adconn.set_user_password("password")

res = adconn.connect
```

### or connect using local credentials cache
```ruby
require 'radcli'
require "rkerberos"

# Kinit using principal name and keytab.
principal = "Administrator"
keytab file over an unsecured network.
keytab="/etc/foreman-proxy/ad.keytab"
krb5 = Kerberos::Krb5.new
ccache = Kerberos::Krb5::CredentialsCache.new
krb5.get_init_creds_keytab principal, keytab, nil, ccache

# Connect

adconn = Adcli::AdConn.new("example.com")
adconn.set_domain_realm("EXAMPLE.COM")
adconn.set_domain_controller("dc.example.com")

adconn.set_login_ccache_name("")

res = adconn.connect
```

### Join
```ruby

enroll = Adcli::AdEnroll.new(adconn)
enroll.set_computer_name("server")
enroll.set_host_fqdn("server.example.com")
enroll.set_computer_password("password")

enroll.join()
```

### Reset Password
```ruby

enroll = Adcli::AdEnroll.new(adconn)
enroll.set_computer_name("server")
enroll.set_computer_password("newpass")

enroll.password()

```

### Delete
```ruby

enroll = Adcli::AdEnroll.new(adconn)
enroll.set_computer_name("server")

enroll.delete()
```

# Notes
For a testing environment you need the following:

* A windows domain controller and a connected linux server.
* The linux server must be able to resolve domain names from the domains dns server.

# Authors
* Mårten Cassel
 
