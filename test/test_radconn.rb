########################################################################
# test_radconn.rb
#
# Test suite for the Adcli::Adconn class. 
#
require 'rubygems'
gem 'test-unit'

require 'test/unit'
require 'radcli'

class TC_Adconn < Test::Unit::TestCase
  def setup
    @domain = "TEST.DOMAIN"
    @realm = "TEST.REALM"
    @domain_controller = "TEST-DC"
    @ccache_name = "testccache"
    @login_user = "testuser"
    @user_password = "testpassword"

    @conn = Adcli::AdConn.new(@domain)
  end

  test "an error is raised on connect if an invalid domain controller is used" do
    @conn.set_login_user("Administrator")
    @conn.set_user_password("password")
    @conn.set_domain_realm("EXAMPLE.COM")
    @conn.set_domain_controller("foo.example.com")

    exception = assert_raises(RuntimeError) { @conn.connect }
    assert_equal("Couldn't resolve host name: foo.example.com: Name or service not known", exception.message)
  end
  
  test "an error is raised on connect if an invalid realm is used" do
    @conn.set_login_user("Administrator")
    @conn.set_user_password("password")
    @conn.set_domain_realm("EXAMPLE.INCORRECT")
    @conn.set_domain_controller("dc.example.com")

    exception = assert_raises(RuntimeError) { @conn.connect }
  end
  
  test "argument to constructor must be a string" do
    assert_raise(TypeError){ Adcli::AdConn.new(1) }
    assert_raise(TypeError){ Adcli::AdConn.new(true) }
  end
  
  test "constructor accepts a domain name" do
    assert_nothing_raised{ Adcli::AdConn.new('domain') }
  end

  test "argument to domain realm setter must be a string" do
    assert_raise(TypeError){ @conn.set_domain_realm(1) }
    assert_raise(TypeError){ @conn.set_domain_realm(true) }
  end

  test "domain realm setter/getter sets/returns value" do
    @conn.set_domain_realm(@realm)
    realm = @conn.get_domain_realm()
    assert_equal(@realm, realm)
  end

  test "argument to domain controller setter must be a string" do
    assert_raise(TypeError){ @conn.set_domain_controller(1) }
    assert_raise(TypeError){ @conn.set_domain_controller(true) }
  end
  
  test "domain controller setter/getter sets/returns value" do
    @conn.set_domain_controller(@domain_controller)
    domain_controller = @conn.get_domain_controller()
    assert_equal(@domain_controller, domain_controller)
  end

  test "argument to ccache-name setter must be a string" do
    assert_raise(TypeError){ @conn.set_login_ccache_name(1) }
    assert_raise(TypeError){ @conn.set_login_ccache_name(true) }
  end

  test "login ccache name setter/getter sets/returns value" do
    @conn.set_login_ccache_name(@ccache_name)
    login_ccache = @conn.get_login_ccache_name()
    assert_equal(@ccache_name, login_ccache)
  end

  test "argument to login user setter must be a string" do
    assert_raise(TypeError){ @conn.set_login_user(1) }
    assert_raise(TypeError){ @conn.set_login_user(true) }
  end

  test "login user setter/getter sets/returns value" do
    @conn.set_login_user(@login_user)
    login_user = @conn.get_login_user()
    assert_equal(@login_user, login_user)
  end

  test "argument to login password setter must be a string" do
    assert_raise(TypeError){ @conn.set_user_password(1) }
    assert_raise(TypeError){ @conn.set_user_password(true) } 
  end
  
  test "login password setter/getter sets/returns value" do
    @conn.set_user_password(@user_password)
    password = @conn.get_user_password()
    assert_equal(@user_password, password)
  end
 
end
