#include <ruby.h>
#include <radcli.h>

VALUE m_adcli;
VALUE c_adconn_exception;

void Init_radcli() {
    m_adcli = rb_define_module("Adcli");

    Init_AdConn();
    Init_AdEnroll();
}
