########################################################################
# test_radenroll.rb
#
# Test suite for the Adcli::AdEnroll
#
require 'rubygems'
gem 'test-unit'

require 'test/unit'
require 'radcli'

class TC_AdEnroll < Test::Unit::TestCase
  def setup
    @domain = "TEST.DOMAIN"
    @realm = "TEST.REALM"
    @domain_controller = "TEST-DC"
    @ccache_name = "testccache"
    @login_user = "testuser"
    @user_password = "testpassword"

    @host_fqdn = "computer.test.domain"
    @computer_name = "computer"
    @computer_password = "computer-password"

    @conn = Adcli::AdConn.new(@domain)
    @enroll = Adcli::AdEnroll.new(@conn)
  end
  
  test "argument to constructor must be a string" do
    assert_raise(TypeError){ Adcli::AdEnroll.new(1) }
    assert_raise(TypeError){ Adcli::AdEnroll.new(true) }
  end
  
  test "constructor accepts a connection object" do
    assert_nothing_raised{ Adcli::AdEnroll.new(@conn) }
  end

  test "host fqdn setter/getter sets/returns value" do
    @enroll.set_host_fqdn(@host_fqdn)
    host_fqdn = @enroll.get_host_fqdn()
    assert_equal(@host_fqdn, host_fqdn)
  end

  test "computer name setter/getter sets/returns value" do
    @enroll.set_computer_name(@computer_name)
    computer_name = @enroll.get_computer_name()
    assert_equal(@computer_name, computer_name)
  end

  test "computer password setter/getter sets/returns value" do
    @enroll.set_computer_password(@computer_password)
    computer_password = @enroll.get_computer_password()
    assert_equal(@computer_password, computer_password)
  end

  def teardown
  end

end
