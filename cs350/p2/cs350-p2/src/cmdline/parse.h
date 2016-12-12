#ifndef __PARSE_COMMAND_LINE__
#define __PARSE_COMMAND_LINE__

/* ************************************************************************* *
 * The purpose of the #ifndef ... #define ... #endif structure is to prevent *
 * this code from being included multiple times caused by nested #include    *
 * statements. This comment can be removed.                                  *
 * ************************************************************************* */

/* ************************************************************************* *
 * parse.h                                                                   *
 * -------                                                                   *
 *  Author:   Conner Turnbull                                                *
 *  Purpose:  Header file for parse.c.                                       *
 * ************************************************************************* */


/* ************************************************************************* *
 * Library includes here. If none needed, delete this comment.               *
 * ************************************************************************* */
#include <stdint.h>             /* uint32_t, uint8_t, and similar types */
#include <inttypes.h>
#include <stdlib.h>             /* malloc */

#include "../output/print.h"

/* ************************************************************************* *
 * Function prototypes here. Note that variable names are often omitted.     *
 * ************************************************************************* */
int parse_command_line (int, char **);

/* ************************************************************************* *
 * Externally defined variables here. An externally defined variable is a    *
 * global variable in parse.c that is made to be accessible to parts of the  *
 * program that include this header file. For instance, if you have a global *
 * variable defined as:                                                      *
 *                                                                           *
 *   bool some_global_boolean;                                               *
 *                                                                           *
 * In this file, you would put:                                              *
 *                                                                           *
 *   extern bool some_global_boolean;                                        *
 *                                                                           *
 * This comment should be deleted.                                           *
 * ************************************************************************* */
extern const char *pep8_code_file, *sym_list_file;
extern uint32_t verbose, interpreter, symbol;
#endif
