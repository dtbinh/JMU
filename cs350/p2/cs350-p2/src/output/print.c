/* ************************************************************************* *
 * print.c                                                                   *
 * ------                                                                    *
 *  Author:   Conner Turnbull                                                *
 *  Purpose:  Houses custom print functions                                  *
 * ************************************************************************* */

/* ************************************************************************* *
 * Library includes here.  For documentation of standard C library           *
 * functions, see the list at:                                               *
 *   http://pubs.opengroup.org/onlinepubs/009695399/functions/contents.html  *
 * ************************************************************************* */
#include "print.h"

/* ************************************************************************* *
 * printv -- When verbose, prints  messages in green. This is a near direct  *
 *           copy of printf                                                  *
 *                                                                           *
 * Parameters                                                                *
 *   msg -- the message to be printed                                        *
 *                                                                           * 
 * Returns                                                                   *
 *   If successful, the total number of characters written is returned.      *
 *   On failure, a negative number is returned.                              *
 *   http://www.tutorialspoint.com/c_standard_library/c_function_printf.htm  *
 * ************************************************************************* */

 int
 printv (char *format, ...)
 {
    va_list arg;
    int done;

    if (verbose)
    {
        //Concat the strings for pretty colors. +1 for \x00
        va_start (arg, format);
        done = vfprintf (stdout, format, arg);
        va_end (arg);

    }
    else
    {
        va_start (arg, format);
        done = 0;
        va_end (arg);
    }

    return done;
 }


/* ************************************************************************* *
 * print_dis - Prints dis. Formats and prints the assembly code provided     *
 *                                                                           *
 * Parameters                                                                *
 *   list -- the first node in the linked list of instruction_t structs.     *
 *                                                                           * 
 * Returns                                                                   *
 *   Program exit status. The standard is to return 0 for normal exit (no    *
 *   errors occurred). If something unusual happens, return some number      *
 *   other than 0, which can then indicate to the user what happened.        *
 * ************************************************************************* */
void
print_dis(instruction_t **list)
{
    instruction_t *root = *list;
    
    printf("Addr\tCode\tMnemon\tOperand\n");

    instruction_t *cur = root;
    while (cur -> next != NULL)
    {
        if (cur -> unary == 0)
        {
            printf("%04X\t%02X%04X\t%s\t0x%04X,%s\n", cur -> address,
                                                      cur -> inst_spec,
                                                      cur -> op_spec,
                                                      cur -> mnemonic,
                                                      cur -> op_spec,
                                                      cur -> addressing_mode);
        }
        else
        {
            printf("%04X\t%02X\t%s\n", cur -> address, cur -> inst_spec,
                                       cur -> mnemonic);
        }
        cur = cur -> next;
    }
}


/* ************************************************************************* *
 * start - Used for formatting output only. Prints out a line of dashes      *
 *                                                                           *
 * Parameters                                                                *
 *                                                                           * 
 * Returns                                                                   *
 *   void                                                                    *
 * ************************************************************************* */
void
start()
{
    printf("-----------------------------------\n");
}


/* ************************************************************************* *
 * printc - Prints the contents of the cpu                                   *
 *                                                                           *
 * Parameters                                                                *
 *   cpu -- pointer to the cpu struct                                        *
 *                                                                           * 
 * Returns                                                                   *
 *   void                                                                    *
 * ************************************************************************* */
void printc(cpu_t * cpu)
{
    printf("Status bits (NZVC)         %u %u %u %u\n",
                                              (cpu -> NZVC & 0x08) >> 3,
                                              (cpu -> NZVC & 0x04) >> 2,
                                              (cpu -> NZVC & 0x02) >> 1,
                                               cpu -> NZVC & 0x01);
    printf("Accumulator (A)            0x%04X\n", cpu -> A);
    printf("Index register (X)         0x%04X\n", cpu -> X);
    printf("Program counter (PC)       0x%04X\n", cpu -> PC);
    printf("Instruction register (IR)  0x%02X%04X\n", cpu -> inst_spec,
                                                      cpu -> op_spec);
    printf("-----------------------------------\n");
}


/* ************************************************************************* *
 * DECO - outputs a decimal number                                           *
 *                                                                           *
 * Parameters                                                                *
 *   number -- the number                                                    *
 *                                                                           * 
 * Returns                                                                   *
 *   void                                                                    *
 * ************************************************************************* */
void
DECO (uint16_t number)
{
    uint16_t num = number;
    if ((num & 0x8000) == 0x8000)
    {
        num -= 1;
        num = ~(num);
        printf ("  Output -%d\n", num);
        printf ("-----------------------------------\n");
    }
    else
    {
        printf ("  Output %d\n", num);
        printf ("-----------------------------------\n");
    }
}


/* ************************************************************************* *
 * CHARO - outputs a char                                                    *
 *                                                                           *
 * Parameters                                                                *
 *   value -- the hex value of the char                                      *
 *                                                                           * 
 * Returns                                                                   *
 *   void                                                                    *
 * ************************************************************************* */
void
CHARO (uint8_t num)
{
    printf ("  Output '%c'\n", num);
    printf ("-----------------------------------\n");
}


/* ************************************************************************* *
 * memory_change - Displays the change in memory                             *
 *                                                                           *
 * Parameters                                                                *
 *   addr -- address in memory being changed                                 *
 *   op_spec -- the value being placed into the memory location              *
 *                                                                           * 
 * Returns                                                                   *
 *   void                                                                    *
 * ************************************************************************* */
void
memory_change (uint16_t addr, uint16_t op_spec)
{
    printf ("  Mem[%04X] <-- 0x%04X\n", addr, op_spec);
    printf ("-----------------------------------\n");
}
