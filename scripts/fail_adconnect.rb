#!/usr/bin/env ruby
 
require 'radcli'

# Couldn't resolve host name: foo.example.com: Name or service not known

adconn = Adcli::AdConn.new("example.com")
adconn.set_login_user("Administrator")
adconn.set_user_password("password")
adconn.set_domain_realm("EXAMPLE.COM")
adconn.set_domain_controller("foo.example.com")

begin
  res = adconn.connect
rescue => error
  puts error
end

# Couldn't get kerberos ticket for: Administrator@EXAMPLE.INCORRECT: Cannot find KDC for realm "EXAMPLE.INCORRECT"

adconn = Adcli::AdConn.new("example.com")
adconn.set_login_user("Administrator")
adconn.set_user_password("password")
adconn.set_domain_realm("EXAMPLE.INCORRECT")
adconn.set_domain_controller("dc.example.com")

begin
  res = adconn.connect
rescue => error
  puts error
end

# Couldn't authenticate as: Administrator@EXAMPLE.COM: Preauthentication failed

adconn = Adcli::AdConn.new("example.com")
adconn.set_login_user("Administrator")
adconn.set_user_password("incorrect")
adconn.set_domain_realm("EXAMPLE.COM")
adconn.set_domain_controller("dc.example.com")

begin
  res = adconn.connect
rescue => error
  puts error
end

