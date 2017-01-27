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

### or connect using local credentials cache
```ruby
require 'radcli'
require "rkerberos"

# Kinit using principal name and keytab.
principal = "Administrator"
# !!!You should always store keytab files on a local disk, and make them readable only by the root user. Also, you should never send a keytab file over an unsecured network.
keytab="/tmp/realm_ad.keytab"
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
* Sleep
* Decide what to test, implement tests. Study rkerberos tests.
* Return error codes from adcli library. Remove printing errors.
* Let the radcli user check error codes.
* Let the user print errors using the function (adutil.h: adcli_get_last_error)
* adcli_result: ADCLI_SUCCESS, ADCLI_ERR_UNEXPECTED, ADCLI_ERR_FAIL, ADCLI_ERR_DIRECTORY, ADCLI_ERR_CONFIG, ADCLI_ERR_CREDENTIALS.
  
