#include <radcli.h>
 
VALUE c_adconn;

// Free function for the Adcli::Adconn class.
static void radcli_free (RUBY_ADCONN* ptr) {
    if(!ptr)
        return;
    adcli_conn_unref (ptr->conn);
    free (ptr);
}

// Allocation function for the Adcli:Adconn class.
static VALUE radconn_allocate (VALUE klass) {
    RUBY_ADCONN* ptr = malloc (sizeof(RUBY_ADCONN));
    memset (ptr, 0, sizeof(RUBY_ADCONN));
    return Data_Wrap_Struct (klass, 0, radcli_free, ptr);
}

/*
 * call-seq:
 *  Adcli::Adconn.new("domain.com")
 * 
 * Creates and returns a new Adcli::Adconn object. 
 */
static VALUE radconn_initialize (VALUE self, VALUE domain) {
    RUBY_ADCONN* ptr;
    const char *domain_name = StringValuePtr(domain);
    Data_Get_Struct (self, RUBY_ADCONN, ptr);
    ptr->conn = adcli_conn_new (domain_name);
    return self;
}

/* 
 * call-seq:
    Adcli::Adconn.set_login_ccache_name("")

   Set the login kerberos cache name
*/
static VALUE radconn_set_login_ccache_name (VALUE self, VALUE ccname) {
    RUBY_ADCONN* ptr;
    const char *c_ccname = StringValuePtr(ccname);
    Data_Get_Struct (self, RUBY_ADCONN, ptr);
    adcli_conn_set_login_ccache_name (ptr->conn, c_ccname);
    return self;
}

/*
 * call-seq:
 *  Adcli::Adconn.set_login_user("user")
 *
 * Sets the login user that we should authenticate as.
 */
static VALUE radconn_set_login_user (VALUE self, VALUE user) {
    RUBY_ADCONN* ptr;
    const char *c_user = StringValuePtr(user);
    Data_Get_Struct (self, RUBY_ADCONN, ptr);
    adcli_conn_set_login_user (ptr->conn, c_user);
    return self;
}
 
/*
 * call-seq:
 *  Adcli::Adconn.get_login_user # => 'user'
 *
 * Get the login user for authentication.
 */
 static VALUE radconn_get_login_user (VALUE self) {
    RUBY_ADCONN* ptr;
    const char *login_user = NULL;
    Data_Get_Struct (self, RUBY_ADCONN, ptr);
    login_user = adcli_conn_get_login_user (ptr->conn);
    return rb_str_new_cstr (login_user);
}

/*
 * call-seq:
 *  Adcli::Adconn.set_user_password
 *
 * Sets the login user password for authentication.
 */
static VALUE radconn_set_user_password (VALUE self, VALUE password) {
    RUBY_ADCONN* ptr;
    const char *c_password = StringValuePtr(password);
    Data_Get_Struct (self, RUBY_ADCONN, ptr);
    adcli_conn_set_user_password (ptr->conn, c_password);
    return self;
}
 
/*
 * call-seq:
 *  Adcli::Adconn.get_user_password
 *
 * Gets the login user password for authentication.
 */
static VALUE radconn_get_user_password (VALUE self) {
    RUBY_ADCONN* ptr;
    const char *login_password = NULL;
    Data_Get_Struct (self, RUBY_ADCONN, ptr);
    login_password = adcli_conn_get_user_password(ptr->conn);
    return rb_str_new_cstr(login_password);
}

/*
 * call-seq:
 *  Adcli::Adconn.get_domain_realm # => 'YOUR.REALM.COM'
 *
 * Gets the domain realm.
 */
static VALUE radconn_get_domain_realm (VALUE self) {
    RUBY_ADCONN* ptr;
    const char *domain_realm = NULL;
    Data_Get_Struct (self ,RUBY_ADCONN, ptr);
    domain_realm  = adcli_conn_get_domain_realm(ptr->conn);
    return rb_str_new_cstr (domain_realm);
} 

/*
 * call-seq:
 *  Adcli::Adconn.set_domain_realm('YOUR.REALM.COM')
 *
 * Set the domain realm.
 */
static VALUE radconn_set_domain_realm (VALUE self, VALUE domain_realm) {
    RUBY_ADCONN* ptr;
    char *c_domain_realm = StringValuePtr(domain_realm);
    Data_Get_Struct (self, RUBY_ADCONN, ptr);
    adcli_conn_set_domain_realm (ptr->conn, c_domain_realm);
    return self;
}


/*
 * call-seq:
 *  Adcli::Adconn.get_domain_controller #=> 'YOUR.DC.REALM.COM'
 *
 * Get the domain controller to use.
 */
static VALUE radconn_get_domain_controller (VALUE self) {
    RUBY_ADCONN* ptr;
    const char *domain_controller = NULL;
    Data_Get_Struct (self ,RUBY_ADCONN, ptr);
    domain_controller = adcli_conn_get_domain_controller (ptr->conn);
    return rb_str_new_cstr (domain_controller);
} 

/*
 * call-seq:
 *  Adcli::Adconn.set_domain_controller('YOUR.DC.REALM.COM')
 *
 * Get the domain controller to use.
 */
static VALUE radconn_set_domain_controller (VALUE self, VALUE domain_controller) {
    RUBY_ADCONN* ptr;
    char *c_domain_controller = StringValuePtr (domain_controller);
    Data_Get_Struct (self, RUBY_ADCONN, ptr);
    adcli_conn_set_domain_controller (ptr->conn, c_domain_controller);
    return self;
}

/*
 * call-seq:
 *  Adcli::Adconn.connect
 *
 * Connect to Active Directory and authenticate using the login username and password.
 */
static VALUE radconn_connect (VALUE self) {
    RUBY_ADCONN* ptr;
    adcli_result res;
    Data_Get_Struct (self ,RUBY_ADCONN, ptr);
    res = adcli_conn_connect (ptr->conn);
    if (res != ADCLI_SUCCESS) {
        fprintf(stderr, adcli_get_last_error());
    }
    return self;
}

void Init_AdConn()
{
    c_adconn = rb_define_class_under (m_adcli, "AdConn", rb_cObject);

    // Allocate functions
    rb_define_alloc_func (c_adconn, radconn_allocate);

    // Initializers
    rb_define_method (c_adconn, "initialize", radconn_initialize, 1);

    // AdConn Methods
    rb_define_method (c_adconn, "set_login_ccache_name", radconn_set_login_ccache_name, 1);
    rb_define_method (c_adconn, "get_login_user", radconn_get_login_user, 0);
    rb_define_method (c_adconn, "set_login_user", radconn_set_login_user, 1);
    rb_define_method (c_adconn, "get_user_password", radconn_get_user_password, 0);
    rb_define_method (c_adconn, "set_user_password", radconn_set_user_password, 1);
    rb_define_method (c_adconn, "get_domain_realm", radconn_get_domain_realm, 0);
    rb_define_method (c_adconn, "set_domain_realm", radconn_set_domain_realm, 1);
    rb_define_method(c_adconn, "get_domain_controller", radconn_get_domain_controller, 0);
    rb_define_method(c_adconn, "set_domain_controller", radconn_set_domain_controller, 1);
    rb_define_method(c_adconn, "connect", radconn_connect, 0);
}
