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
 *  Author:   CONNER TURNBULL                                                *
 *  Purpose:  Header file for parse.c.                                       *
 * ************************************************************************* */


/* ************************************************************************* *
 * Library includes here. If none needed, delete this comment.               *
 * ************************************************************************* */
#include "../campus/map.h"          /* building/area types and constants */
#include "../cmdline/parse.h"


/* ************************************************************************* *
 * Function prototypes here. Note that variable names are often omitted.     *
 * ************************************************************************* */
void print_area (campus_t area);
void print_building (building_t building);
void print_distance (uint32_t distance);
void print_decimal(uint8_t*, int);
void print_octal(uint8_t*, int);
void print_hex(uint8_t*, int);

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

#endif
