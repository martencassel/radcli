########################################################################
# test_radconn.rb
#
# Test suite for the Adcli::Adconn class. This suite requires
# that you have a Active Directory domain controller with the domain name "example.com"
# connected to this machine.
#
require 'rubygems'
gem 'test-unit'

require 'radcli'
include Adcli

class TC_Adconn< Test::Unit::TestCase
    def self.startup
        conn = AdConn.new(domain_name)
    end

#    test ""

    def setup
        @domain_name = "example.com"
        @adconn = Adcli::AdConn.new(@domain_name)
    end

    def teardown
        @adconn = nil
    end
end
