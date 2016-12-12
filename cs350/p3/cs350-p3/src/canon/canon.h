#ifndef __CANON_REP__
#define __CANON_REP__


/* ************************************************************************* *
 * canon.h                                                                   *
 * -------                                                                   *
 *  Author:   Conner Turnbull                                                *
 *  Purpose:  Header file for canon.c.                                       *
 * ************************************************************************* */


/* ************************************************************************* *
 * Library includes here. If none needed, delete this comment.               *
 * ************************************************************************* */
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

/* ************************************************************************* *
 * Function prototypes here. Note that variable names are often omitted.     *
 * ************************************************************************* */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int build_canon (const char *);

extern const char * STR_CONST[];

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
