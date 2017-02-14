#ifndef ADCLI_H_INCLUDED
#define ADCLI_H_INCLUDED

#include <ruby.h>
#include <adconn.h>
#include <adenroll.h>
#include <stdio.h>
#include <errno.h>

// Function prototypes
void Init_AdConn();
void Init_AdEnroll();

// Variable declarations
extern VALUE m_adcli;
extern VALUE c_adconn;
extern VALUE c_adenroll;
extern VALUE c_adconn_exception;

// Adcli::AdConn
typedef struct {
    adcli_conn *conn;
} RUBY_ADCONN;

// Adcli::AdEnroll
typedef struct {
    adcli_enroll *enroll;
} RUBY_ADENROLL;

#endif
