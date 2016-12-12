#ifndef __DISASSEMBLE__
#define __DISASSEMBLE__

/* ************************************************************************* *
 * disassemble.h                                                             *
 * -------                                                                   *
 *  Author:   Conner Turnbull                                                *
 *  Purpose:  Header file for disassemble.c                                  *
 * ************************************************************************* */


/* ************************************************************************* *
 * Library includes here. If none needed, delete this comment.               *
 * ************************************************************************* */
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

/* ************************************************************************* *
 * Function prototypes here. Note that variable names are often omitted.     *
 * ************************************************************************* */
struct instruction_t;

typedef struct instruction_t
{
    uint16_t address;
    uint8_t inst_spec;
    uint16_t op_spec;
    int unary; //1 when unary, 0 when not
    char *addressing_mode;
    char *mnemonic;
    struct instruction_t *next;
} instruction_t;

struct symb_t;

typedef struct symb_t
{
    char * symbol;
    char * pseudo_op;
    uint32_t addr;
    uint32_t size;
} symb_t;

int disassemble(instruction_t **, uint8_t **code_array, uint32_t bytes_in_array);
void free_list (instruction_t **);

#endif
