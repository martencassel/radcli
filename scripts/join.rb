#!/usr/bin/env ruby
 
require 'radcli'

adconn = Adcli::AdConn.new("example.com")
adconn.set_login_user("Administrator")
adconn.set_user_password("password")
adconn.set_domain_realm("EXAMPLE.COM")
adconn.set_domain_controller("dc.example.com")
res = adconn.connect

enroll = Adcli::AdEnroll.new(adconn)
enroll.set_host_fqdn("server.example.com")
enroll.set_computer_name("server")
enroll.set_computer_password("password")

begin
  enroll.join()
rescue => error
  puts error
end

