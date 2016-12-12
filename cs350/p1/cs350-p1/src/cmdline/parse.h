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
 *  Author:   CONNER TURNBULL                                                *
 *  Purpose:  Header file for parse.c.                                       *
 * ************************************************************************* */


/* ************************************************************************* *
 * Library includes here. If none needed, delete this comment.               *
 * ************************************************************************* */

#include <stdint.h>

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
extern uint8_t verbose, map_mode, building, area, distance, decimal, octal, help;
extern const char *file_name, *building_arg, *area_arg;
extern char *distance_arg;
#endif
