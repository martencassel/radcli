#include <radcli.h>

VALUE c_adenroll;

// Free function for the Adcli::AdEnroll class.
static void radenroll_free (RUBY_ADENROLL *ptr) {
    if(!ptr)
        return;
    adcli_enroll_unref (ptr->enroll);
    free (ptr);
}

// Allocation function for the Adcli:AdEnroll class.
static VALUE radenroll_allocate (VALUE klass) {
    RUBY_ADENROLL *ptr = malloc (sizeof(RUBY_ADENROLL));
    memset (ptr, 0, sizeof(RUBY_ADENROLL));
    return Data_Wrap_Struct (klass, 0, radenroll_free, ptr);
}

/*
 * call-seq:
 *  conn_object = Adcli::AdConn.connect('YOUR.REALM.COM')
 *  Adcli::AdEnroll.new(conn_object)
 * 
 * Creates and returns a new Adcli::AdEnroll object. 
 */
static VALUE radenroll_initialize (VALUE self, VALUE ad_conn) {
    RUBY_ADCONN *ptr_conn;
    RUBY_ADENROLL *ptr_enroll;
    Data_Get_Struct (ad_conn, RUBY_ADCONN, ptr_conn);
    Data_Get_Struct (self, RUBY_ADENROLL, ptr_enroll);
    adcli_enroll *enroll = adcli_enroll_new (ptr_conn->conn);
    ptr_enroll->enroll = enroll;
    return self;
}

/*
 * call-seq:
 *  
 *  adenroll.get_computer_name # => hostname.your.realm.com
 * 
 * Creates and returns the computer name.
 */
static VALUE radenroll_get_computer_name (VALUE self) {
    RUBY_ADENROLL *ptr_enroll;
    const char *c_computer_name = NULL;
    Data_Get_Struct (self ,RUBY_ADENROLL, ptr_enroll);
    c_computer_name  = adcli_enroll_get_computer_name (ptr_enroll->enroll);
    return rb_str_new_cstr (c_computer_name);
}

/*
 * call-seq:
 *  
 *  adenroll.set_computer_name('hostname')
 * 
 * Set the computer name to do the enroll operation on (join or delete).
 */
static VALUE radenroll_set_computer_name (VALUE self, VALUE value) {
    RUBY_ADENROLL *ptr_enroll;
    adcli_enroll *enroll;
    adcli_result res;
    const char *c_value = StringValuePtr (value);
    Data_Get_Struct (self, RUBY_ADENROLL, ptr_enroll);
    enroll = ptr_enroll->enroll;
    adcli_enroll_set_computer_name (enroll, c_value);
    return self;
}

/*
 * call-seq:
 *  
 *  adenroll.get_computer_password
 * 
 * Gets the computer password 
 */
static VALUE radenroll_get_computer_password (VALUE self) {
    RUBY_ADENROLL *ptr_enroll;
    const char *c_computer_password = NULL;
    Data_Get_Struct (self ,RUBY_ADENROLL, ptr_enroll);
    c_computer_password = adcli_enroll_get_computer_password (ptr_enroll->enroll);
    return rb_str_new_cstr (c_computer_password);
}

/*
 * call-seq:
 *  
 *  adenroll.set_computer_password('computer-password')
 * 
 * Sets the computer password 
 */
static VALUE radenroll_set_computer_password (VALUE self, VALUE value) {
    RUBY_ADENROLL *ptr_enroll;
    adcli_enroll *enroll;
    adcli_result res;
    const char *c_value = StringValuePtr (value);
    Data_Get_Struct (self, RUBY_ADENROLL, ptr_enroll);
    enroll = ptr_enroll->enroll;
    adcli_enroll_set_computer_password (enroll, c_value);
    return self;
}

/*
 * call-seq:
 *  
 *  adenroll.join
 * 
 * Joins a new computer to the Active Directory domain. Creates a machine account and sets a password for it.
 */                 
static VALUE radenroll_join (VALUE self) {
    RUBY_ADENROLL *ptr_enroll;
    adcli_result res;
    Data_Get_Struct (self, RUBY_ADENROLL, ptr_enroll);
    res = adcli_enroll_join (ptr_enroll->enroll, ADCLI_ENROLL_NO_KEYTAB);
    if (res != ADCLI_SUCCESS) {
        fprintf(stderr, "failed to join: %s", adcli_get_last_error());
    }
    return self;
}

/*
 * call-seq
 *
 * adenroll.enroll_password
 * 
 * Updates a computer password 
 */
static VALUE radenroll_password (VALUE self) {
    RUBY_ADENROLL *ptr_enroll;
    adcli_result res;
    Data_Get_Struct (self, RUBY_ADENROLL, ptr_enroll);
    res = adcli_enroll_password (ptr_enroll->enroll, ADCLI_ENROLL_PASSWORD_VALID);
    if (res != ADCLI_SUCCESS) {
        fprintf(stderr, "failed to update computer: %s", adcli_get_last_error());
    }
    return self;
}


/*
 * call-seq:
 *  
 *  adenroll.delete
 * 
 * Delets a existing computer from the Active Directory domain
 */   
static VALUE radenroll_delete (VALUE self) {
    RUBY_ADENROLL *ptr_enroll;
    adcli_result res;
    Data_Get_Struct (self, RUBY_ADENROLL, ptr_enroll);
    res = adcli_enroll_delete (ptr_enroll->enroll, 0);
    if (res != ADCLI_SUCCESS) {
        fprintf(stderr, "failed to delete computer: %s", adcli_get_last_error());
    }
    return self;
}

void Init_AdEnroll()
{
    c_adenroll = rb_define_class_under (m_adcli, "AdEnroll", rb_cObject);
    rb_define_alloc_func (c_adenroll, radenroll_allocate);
    rb_define_method (c_adenroll, "initialize", radenroll_initialize, 1);

    rb_define_method (c_adenroll, "join", radenroll_join, 0);
    rb_define_method (c_adenroll, "password", radenroll_password, 0);
    rb_define_method (c_adenroll, "delete", radenroll_delete, 0);

    rb_define_method (c_adenroll, "get_computer_name", radenroll_get_computer_name, 0);
    rb_define_method (c_adenroll, "set_computer_name", radenroll_set_computer_name, 1);

    rb_define_method (c_adenroll, "get_computer_password", radenroll_get_computer_password, 0);
    rb_define_method (c_adenroll, "set_computer_password", radenroll_set_computer_password, 1);

}
