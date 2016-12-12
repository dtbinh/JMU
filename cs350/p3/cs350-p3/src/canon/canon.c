/* ************************************************************************* *
 * main.c                                                                    *
 * ------                                                                    *
 *  Author:   Conner Turnbull                                                *
 *  Purpose:  This is a template for projects 0 and 1.                       *
 * ************************************************************************* */

/* ************************************************************************* *
 * Library includes here.  For documentation of standard C library           *
 * functions, see the list at:                                               *
 *   http://pubs.opengroup.org/onlinepubs/009695399/functions/contents.html  *
 * ************************************************************************* */
#include "canon.h"
#include "../verilog/codegen.h"

/* ************************************************************************* *
 * Local function declarations                                               *
 * ************************************************************************* */
void expand (const char *, ast_t *);

/* ************************************************************************* *
 * Global variable declarations                                              *
 * ************************************************************************* */

/* ************************************************************************* *
 * build_canon -- Builds the canoninical representation of the ast. This     *
 *                algorithm passes twice through the ast. The first pass     *
 *                builds the unexpanded output, the second expands           *
 *                expressions beneath           *
 *                                                                           *
 * Parameters                                                                *
 *   ast -- Pointer to the AST linked list                                   *
 *                                                                           *
 * Returns                                                                   *
 *   String canoninical representation of the AST. If an error is            *
 *   encountered, NULy is returned.                                          *
 * ************************************************************************* */

int
build_canon (const char * filename)
{   
    ast_t * ast = parse_file(filename);
    if (ast == NULL) return 1;

    module_t * module = ast->modules;
    symtab_entry * symbol = NULL;
    assign_entry * assign = NULL;
    binary_op * bop = NULL;
    unary_op * uop = NULL;

    printf ("Building canonical representation for module %s:\n\n", module-> name);
    // Begin loop
    for (symbol = module->symtab; symbol != NULL; symbol = symbol->next)
    {
        printf ("  %s [%s]", symbol->name, STR_CONST[symbol->type]);

        assign = symbol->assign;
        if (assign != NULL)
        {
            switch (assign->type)
            {
                case 12:
                    uop = assign->eval.uop;
                    printf (" = %s(%s)\n", STR_CONST[uop->op], uop->rhs.name);
                    //Find if expansion is needed, then expand
                    symtab_entry * temp_sym = NULL;
                    for (temp_sym = module->symtab; temp_sym != NULL; temp_sym = temp_sym->next)
                    {
                        if (!strcmp (temp_sym->name, uop->rhs.name))
                        {
                            printf ("     >> expanded: %s", STR_CONST[uop->op]);
                            expand (uop->rhs.name, ast);
                            printf ("\n");
                            break;
                        }
                    }
                    break;
                case 13:
                    bop = assign->eval.bop;
                    printf (" = (%s)%s(%s)\n", bop->lhs.name, STR_CONST[bop->op],
                                             bop->rhs.name);
                    //Find if expansion is needed, then expand
                    temp_sym = NULL;
                    for (temp_sym = module->symtab; temp_sym != NULL; temp_sym = temp_sym->next)
                    {
                        if (!strcmp (temp_sym->name, bop->lhs.name))
                        {
                            printf ("     >> expanded: ");
                            expand (bop->lhs.name, ast);
                            printf ("%s", STR_CONST[bop->op]);
                            expand (bop->rhs.name, ast);
                            printf ("\n");
                            break;
                        }
                        else if (!strcmp (temp_sym->name, bop->rhs.name))
                        {
                            printf ("     >> expanded: ");
                            expand (bop->lhs.name, ast);
                            printf ("%s", STR_CONST[bop->op]);
                            expand (bop->rhs.name, ast);
                            printf ("\n");
                            break;
                        }
                    }
                    break;
                default:
                    return 1;
            }
        }
        else
        {
            printf ("\n");
        }

    }
    printf ("\n");
    return 0;
}

void
expand (const char * identifier, ast_t * ast)
{
    module_t * module = ast->modules;
    symtab_entry * symbol = NULL;
    assign_entry * assign = NULL;
    binary_op * bop = NULL;
    unary_op * uop = NULL;

    for (symbol = module->symtab; symbol != NULL; symbol = symbol->next)
    {
        assign = symbol->assign;
        if (!strcmp (symbol->name, identifier) && assign != NULL)
        {
            //check uop or bop
            switch (assign->type)
            {
                case 12:
                    uop = assign->eval.uop;
                    printf ("%s", STR_CONST[uop->op]);
                    if (uop->rtype == IDENT)
                    {
                        printf("(");
                        expand (uop->rhs.name, ast);
                        printf(")");
                    }
                    else if (uop->rtype == UOP)
                    {
                        printf ("%s\n", STR_CONST[uop->rhs.uop->op]);
                        printf("(");
                        expand (uop->rhs.name, ast);
                        printf(")");
                    }
                    else if (uop->rtype == BOP)
                    {
                        printf("(");
                        expand (uop->rhs.bop->lhs.name, ast);
                        printf(")");
                        printf ("%s", STR_CONST[uop->rhs.bop->op]);
                        printf("(");
                        expand (uop->rhs.bop->rhs.name, ast);
                        printf(")");
                    }
                    break;
                case 13:
                    bop = assign->eval.bop;
                    if (bop->ltype == IDENT)
                    {
                        printf("(");
                        expand (bop->lhs.name, ast);
                        printf(")");
                    }
                    else if (bop->ltype == UOP)
                    {
                        printf ("%s", STR_CONST[bop->lhs.uop->op]);
                        printf ("(");
                        expand (bop->lhs.uop->rhs.name, ast);
                        printf (")");
                    }
                    else if (bop->ltype == BOP)
                    {
                        printf("(");
                        expand (bop->rhs.bop->lhs.name, ast);
                        printf(")");
                        printf ("%s", STR_CONST[bop->rhs.bop->op]);
                        printf("(");
                        expand (bop->rhs.bop->rhs.name, ast);
                        printf(")");
                    }
                    printf ("%s", STR_CONST[bop->op]);
                    if (bop->rtype == IDENT)
                    {
                        printf("(");
                        expand (bop->rhs.name, ast);
                        printf(")");
                    }
                    else if (bop->rtype == UOP)
                    {
                        printf ("(");
                        expand (bop->rhs.uop->rhs.name, ast);
                        printf (")");
                    }
                    else if (bop->rtype == BOP)
                    {
                        printf("(");
                        expand (bop->rhs.bop->lhs.name, ast);
                        printf(")");
                        printf ("%s", STR_CONST[bop->rhs.bop->op]);
                        printf("(");
                        expand (bop->rhs.bop->rhs.name, ast);
                        printf(")");
                    }
                default:
                    return;
            }
        }
        else if (!strcmp (symbol->name, identifier) && assign == NULL)
        {
            //found identifier symbol, but doesn't expand
            printf ("%s", identifier);
            return;
        }
    }
}
