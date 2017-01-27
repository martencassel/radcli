# Description
The radcli library provides a Ruby interface for performing actions on a Active Directory domain using the realmd/adcli tool.
(adcli: https://www.freedesktop.org/software/realmd/adcli/devel-building.html)

# Installation

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
gem install pkg/radcli-0.0.1.gem
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

### or connect using local credentials cache (Initialized using kinit from keytab).
```ruby
require 'radcli'

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

# TODO
* Implement precreate, update and delete for smart-proxy realm provider.
* Add tests

  
