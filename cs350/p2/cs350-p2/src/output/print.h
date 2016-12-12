#ifndef __CAMPUS_MAP_PRINTER__
#define __CAMPUS_MAP_PRINTER__

/* ************************************************************************* *
 * The purpose of the #ifndef ... #define ... #endif structure is to prevent *
 * this code from being included multiple times caused by nested #include    *
 * statements. This comment can be removed.                                  *
 * ************************************************************************* */


/* ************************************************************************* *
 * print.h                                                                   *
 * -------                                                                   *
 *  Author:   Conner Turnbull                                                *
 *  Purpose:  Header file for parse.c.                                       *
 * ************************************************************************* */


/* ************************************************************************* *
 * Library includes here. If none needed, delete this comment.               *
 * ************************************************************************* */

#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "../cmdline/parse.h"
#include "../machine/disassemble.h"
#include "../machine/interpret.h"

/* ************************************************************************* *
 * Function prototypes here. Note that variable names are often omitted.     *
 * ************************************************************************* */

int printv (char *, ...);
void print_dis (instruction_t **);
void start ();
void printc (cpu_t *);
void DECO (uint16_t);
void CHARO (uint8_t);
void memory_change (uint16_t, uint16_t);


#endif
