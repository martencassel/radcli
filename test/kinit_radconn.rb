#!/usr/bin/env ruby

require 'radcli'

adconn = Adcli::AdConn.new("example.com")
adconn.set_login_user("Administrator")
adconn.set_domain_realm("EXAMPLE.COM")
adconn.set_domain_controller("dc.example.com")
adconn.set_login_ccache_name("")
res = adconn.connect

print res
