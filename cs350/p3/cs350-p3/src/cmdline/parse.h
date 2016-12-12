#ifndef __PARSE_COMMAND_LINE__
#define __PARSE_COMMAND_LINE__


/* ************************************************************************* *
 * parse.h                                                                   *
 * -------                                                                   *
 *  Author:   Conner Turnbull                                                *
 *  Purpose:  Header file for parse.c.                                       *
 * ************************************************************************* */


/* ************************************************************************* *
 * Library includes here. If none needed, delete this comment.               *
 * ************************************************************************* */
#include <stdarg.h>
#include <stddef.h>

/* ************************************************************************* *
 * Function prototypes here. Note that variable names are often omitted.     *
 * ************************************************************************* */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
int parse_command_line (int, char **);
int printv (char *, ...);


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
extern const char * input_file, * output_file;
extern int produce_ast, produce_xml, verbose;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
