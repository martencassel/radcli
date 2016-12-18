#include <ruby.h>
#include <radcli.h>

VALUE m_adcli;

void Init_radcli() {
    m_adcli = rb_define_module("Adcli");

    Init_AdConn();
    Init_AdEnroll();
}

/*
    x = Adcli.AdConn.new
*/