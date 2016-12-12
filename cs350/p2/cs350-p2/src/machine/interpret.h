#ifndef __INTERPRET__
#define __INTERPRET__

/* ************************************************************************* *
 * interpret.h                                                               *
 * -------                                                                   *
 *  Author:   Conner Turnbull                                                *
 *  Purpose:  Header file for disassemble.c                                  *
 * ************************************************************************* */


/* ************************************************************************* *
 * Library includes here. If none needed, delete this comment.               *
 * ************************************************************************* */
 #include <stdlib.h>
 #include <stdint.h>             /* uint32_t, uint8_t, and similar types */
 #include <stdio.h>

/* ************************************************************************* *
 * Function prototypes here. Note that variable names are often omitted.     *
 * ************************************************************************* */

 typedef struct cpu_t
 {
    uint8_t NZVC;
    uint16_t A;
    uint16_t X;
    uint16_t T;
    uint16_t PC;
    uint8_t inst_spec; //Together, isnt_spec and op_spec represent the IR
    uint16_t op_spec;
    int STOP;
 } cpu_t;

 typedef struct inst_t
 {
    int valid;
    uint16_t address;
    uint8_t inst_spec;
    uint16_t op_spec;
    uint8_t reg;
    char *addr_mode;
    int is_unary;
 } inst_t;

int interpret (uint8_t **, uint32_t);

#endif
