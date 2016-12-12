/* This file is used for parsing the Verilog file. Do NOT change anything here. */

/* ************************************************************************* *
 * codegen.cpp                                                               *
 * -----------                                                               *
 *  Author:   Michael S. Kirkpatrick                                         *
 *  Purpose:  This code uses a visitor pattern to process pieces of Verilog  *
 *            code. While this compiler is written in C++, we include an     *
 *            interface for building the tree representation for C programs. *
 *  Notes:    The framework for this compiler code is derived from           *
 *            http://gnuu.org/2009/09/18/writing-your-own-toy-compiler/      *
 *            I've made many changes, such as switching to a visitor         *
 *            pattern, adding memory clean-up, and creating a C-style        *
 *            front-end to build an AST representation. Not to mention the   *
 *            fact that the language compiled is completely different...     *
 * ************************************************************************* */

#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"
#include "codegen.hpp"
#include "parser.hpp"

/* C++ macro for checking if malloc() returns NULL */
#define NOT_NULL(p) if ((p) == NULL) { cerr << "ERROR: Malloc failed" << endl; return NULL; }

/* C macro for appending an entry to a table */
#define APPEND(T,S,E)                   \
    if (context->T == NULL)             \
        context->T = context->S = E;    \
    else                                \
    {                                   \
        context->S->next = E;           \
        context->S = E;                 \
    }

/* C++ macro for returning from NModule visitor errors */
#define RETURN(S,N)                 \
    {                               \
        cerr << S << N << endl;     \
        context->success = false;   \
        return;                     \
    }

/* C macro for freeing operations in the AST */
#define FREE_SWITCH(TYPE,EVAL)                  \
    switch (TYPE)                               \
    {                                           \
        case UOP:       free_uop (EVAL.uop);    \
                        break;                  \
        case BOP:       free_bop (EVAL.bop);    \
                        break;                  \
        default:        break;                  \
    }

/* External hooks into the Flex/Bison parser generator */
extern NModuleList * programBlock;
extern int yyparse ();
extern FILE * yyin;

/* Local function declarations */
static void free_module (module_t * module, map<const char *, bool> & symbols);
static void free_uop (unary_op * uop);
static void free_bop (binary_op * bop);
static void free_assign (assign_entry * entry);

/* ************************************************************************* *
 * Expression visitors - visit method for subclasses of NExpression          *
 *                                                                           *
 * Parameters                                                                *
 *   exp - call-by-reference parameter to capture the type of expression     *
 *                                                                           *
 * Returns                                                                   *
 *   The evaluated value of the expression. The return type for all of these *
 *   visitors is eval_t, which is a union of types. Assuming we declare      *
 *   eval_t retval to specify the evaluated value, the actual type returned  *
 *   will be based on the particular type of expression. Specifically:       *
 *                                                                           *
 *     NInteger - retval.value is the long value of the integer              *
 *     NIdentifier - retval.name is the const char * pointing to the name    *
 *     NNotOperator - retval.uop is a pointer to the unary operator          *
 *     NAndOperator - retval.bop is a pointer to the binary operator         *
 *     NOrOperator - retval.bop is a pointer to the binary operator          *
 *     NXorOperator - retval.bop is a pointer to the binary operator         *
 *                                                                           *
 * Notes                                                                     *
 *   The purpose of exp is to allow the caller to determine the type of      *
 *   retval. Using exp, the caller knows which retval field to access.       *
 * ************************************************************************* */
eval_t
NInteger::visit (exp_t * exp)
{
    eval_t retval;
    retval.value = this->value;
    *exp = INT;
    return retval;
}

eval_t
NIdentifier::visit (exp_t * exp)
{
    eval_t retval;
    retval.name = this->name;
    *exp = IDENT;
    return retval;
}

eval_t
NNotOperator::visit (exp_t * exp)
{
    eval_t retval;
    retval.uop = (unary_op *)malloc (sizeof (unary_op));
    retval.uop->op = NOT;
    retval.uop->rhs = this->rhs->visit (&retval.uop->rtype);
    *exp = UOP;
    return retval;
}

eval_t
NAndOperator::visit (exp_t * exp)
{
    eval_t retval;
    retval.bop = (binary_op *) malloc (sizeof (binary_op));
    retval.bop->op = AND;
    retval.bop->lhs = this->lhs->visit (&retval.bop->ltype);
    retval.bop->rhs = this->rhs->visit (&retval.bop->rtype);
    *exp = BOP;
    return retval;
}

eval_t
NOrOperator::visit (exp_t * exp)
{
    eval_t retval;
    retval.bop = (binary_op *) malloc (sizeof (binary_op));
    retval.bop->op = OR;
    retval.bop->lhs = this->lhs->visit (&retval.bop->ltype);
    retval.bop->rhs = this->rhs->visit (&retval.bop->rtype);
    *exp = BOP;
    return retval;
}

eval_t
NXorOperator::visit (exp_t * exp)
{
    eval_t retval;
    retval.bop = (binary_op *) malloc (sizeof (binary_op));
    retval.bop->op = XOR;
    retval.bop->lhs = this->lhs->visit (&retval.bop->ltype);
    retval.bop->rhs = this->rhs->visit (&retval.bop->rtype);
    *exp = BOP;
    return retval;
}

/* ************************************************************************* *
 * Statement visitors -- visit method for subclasses of NStatement           *
 *                                                                           *
 * Parameters                                                                *
 *   context - used to keep track of information produced by other visitors  *
 *   exp - call-by-reference parameter to capture the type of expression     *
 *                                                                           *
 * Returns                                                                   *
 *   The evaluated value of the statement. In the case of an assignment, the *
 *   type will be the type of the root of the parse tree for the right-hand  *
 *   side. This will be either INT (w0 = 1), IDENT (w1 = w0), UOP (w2 = ~w0) *
 *   or BOP (w3 = w1 & w0). Note that the expressions could be hierarchical, *
 *   but the type is the root type. In the case of a wire declaration, the   *
 *   type will always be WIRE. Once the type is known (returned in exp), the *
 *   caller can use the appropriate eval_t union type to get the value.      *
 * ************************************************************************* */
eval_t
NAssignment::visit (CodeGenContext * context, exp_t *exp)
{
    exp_t idexp, rhsexp;
    eval_t retval;
    eval_t id = this->lhs->visit (&idexp);
    if (idexp != IDENT)
    {
        cerr << "ERROR: Left-hand side should always return IDENT" << endl;
        *exp = BADEXP;
        return id;
    }

    retval.assign = (assign_entry *) malloc (sizeof (assign_entry));
    retval.assign->name = id.name;
    retval.assign->eval = this->rhs->visit (&rhsexp);
    retval.assign->type = rhsexp;

    *exp = ASSIGN;
    return retval;
}

eval_t
NWireDeclaration::visit (CodeGenContext * context, exp_t *exp)
{
    exp_t idexp;
    eval_t retval;
    eval_t id = this->id->visit (&idexp);
    if (idexp != IDENT)
    {
        cerr << "ERROR: Wire declaration should always return IDENT" << endl;
        *exp = BADEXP;
        return id;
    }
    retval.symbol = (symtab_entry *) malloc (sizeof (symtab_entry));
    retval.symbol->name = id.name;
    retval.symbol->type = WIRE;
    retval.symbol->assign = NULL;
    retval.symbol->next = NULL;
    *exp = DECL;
    return retval;
}

/* Empty class that is just used as a container for statements */
void NBlock::visit (CodeGenContext * context) { }

/* ************************************************************************* *
 * Module visitors -- visit method for NModuleList and NModule               *
 *                                                                           *
 * Parameters                                                                *
 *   context - used to collect information generated by the other visitors   *
 *                                                                           *
 * Returns                                                                   *
 *   None                                                                    *
 *                                                                           *
 * Notes                                                                     *
 *   NModule visitor does a lot of the work. It visits all of the input,     *
 *   output, and statement nodes. For inputs and outputs, it adds the        *
 *   evaluations to the symbol table, checking for rule violations (see      *
 *   below). For statements, it first determines if the statement is a wire  *
 *   declaration or assignment by dynamically casting the statement. In the  *
 *   case of declarations, the visitor adds the entry to the symbol table,   *
 *   again checking for rule violations. For assignments, the visitor visits *
 *   the right-hand side and creates an assignment entry, which is a parse   *
 *   tree representation of the RHS. As Verilog does not allow redefinition  *
 *   of symbols, the visitor ensures the assignments are unique.             *
 *                                                                           *
 *   As an example, consider the following assignment:                       *
 *                                                                           *
 *     w1 = ~i0 | (i1 & i2)                                                  *
 *                                                                           *
 *   In this case, the assign_entry * assign would have the following values *
 *                                                                           *
 *     assign->type = BOP                                                    *
 *     assign->eval.bop = address of the OR binary operator                  *
 *     assign->name = w1                                                     *
 *                                                                           *
 *   As the RHS evaluation translates to a tree when visited, the OR binary  *
 *   operator will identify the next nodes in the hierarchy:                 *
 *                                                                           *
 *     assign->eval.bop->op = OR                                             *
 *     assign->eval.bop->ltype = UOP                                         *
 *     assign->eval.bop->lhs = address of the NOT unary operator             *
 *     assign->eval.bop->rtype = BOP                                         *
 *     assign->eval.bop->rhs = address of the AND binary operator            *
 *                                                                           *
 * Rules for symbol table generation:                                        *
 *   1 - There must be at least one output (no need for a circuit if none)   *
 *   2 - Input symbols cannot have assignments                               *
 *   3 - Cannot declare a local wire that clashes with input/output          *
 *   4 - Cannot repeat assignments for any symbol                            *
 *   5 - Cannot repeat declarations of same type for same symbol             *
 *   6 - Assignments must have a WIRE or OUTPUT declaration                  *
 * Note that there CAN be an input and output that have the same name        *
 *                                                                           *
 * ************************************************************************* */
void
NModuleList::visit (CodeGenContext * context)
{
    for (ModuleList::const_iterator it = this->modules.begin();
            it != this->modules.end(); it++)
    {
        (*it)->visit(context);
    }
}

/* Helper function for keeping track of assignment entries. This function is
 * needed because the find() method on map<const char *,...> does not do
 * string comparison. So, even if the key has the same string value, it might
 * not actually match. We hack our way around this by iterating through the map */
map<const char *,assign_entry*>::const_iterator
find_assign (map<const char *,assign_entry*> * table, const char *str)
{
    for (map<const char *,assign_entry*>::const_iterator iter = table->begin();
            iter != table->end(); iter++)
    {
        if (!strcmp(iter->first,str))
            return iter;
    }
    return table->end();
}

/* Similar helper function to check if a declaration has been added */
bool
symbol_added (map<const char *,decl_t> * table, const char *str, decl_t type)
{
    for (map<const char *,decl_t>::const_iterator iter = table->begin();
            iter != table->end(); iter++)
    {
        /* Note that WIRE declarations cannot repeat with any other type decl */
        if (!strcmp(iter->first,str) && (iter->second == type || type == WIRE))
            return true;
    }
    return false;
}

/* The module visitor. At 125 lines, this is a candidate for refactoring. */
void
NModule::visit (CodeGenContext * context)
{
    eval_t retval;
    exp_t exp;
    symtab_entry * entry = NULL;
    assign_entry * assign = NULL;
    assign_entry * check = NULL;

    /* Keep track of symbol type declarations: */
    map<const char *,decl_t> symbol_list;

    /* Keep track of assignment entries to be added to symbol table entries: */
    map<const char *,assign_entry *> assignments;

    context->name = this->id->name;


    /* Add OUTPUT declarations to symbol table */
    for (WireList::const_iterator iter = this->output->begin();
            iter != this->output->end(); iter++)
    {
        retval = (*iter)->visit (context, &exp);
        if (exp != DECL)
            RETURN ("ERROR: Input declaration should have type DECL", "");

        entry = retval.symbol;

        /* Rule 5: Cannot repeat output declaration */
        if (symbol_added (&symbol_list, entry->name, OUTPUT))
            RETURN ("ERROR: Output added multiple times: ", entry->name);

        symbol_list[entry->name] = entry->type = OUTPUT;
        APPEND (symtab,lastsym,entry)
    }

    /* Rule 1: There must be at least one output */
    if (context->symtab == NULL)
        RETURN ("ERROR: Must declare at least one output", "");

    /* Add INPUT declarations to symbol table */
    for (WireList::const_iterator iter = this->input->begin();
            iter != this->input->end(); iter++)
    {
        retval = (*iter)->visit(context, &exp);
        if (exp != DECL)
            RETURN ("ERROR: Input declaration should have type DECL", "");

        entry = retval.symbol;

        /* Rule 5: Cannot repeat input declaration */
        if (symbol_added (&symbol_list, entry->name, INPUT))
            RETURN ("ERROR: Input added multiple times: ", entry->name);

        symbol_list[entry->name] = entry->type = INPUT;
        context->lastsym->next = entry;
        context->lastsym = context->lastsym->next;
    }

    /* Build list of assignments, added WIRE declarations to symbol table */
    for (StatementList::const_iterator iter = this->statements->statements.begin();
            iter != this->statements->statements.end(); iter++)
    {
        NAssignment * asst = dynamic_cast<NAssignment*>(*iter);
        if (asst != NULL) /* Statement is an assignment */
        {
            retval = asst->visit (context, &exp);
            if (exp != ASSIGN)
                RETURN ("ERROR: Input declaration should have type ASSIGN", "");

            assign = retval.assign;

            /* Rule 4: Cannot repeat assignments for same symbol */
            if (find_assign (&assignments, assign->name) != assignments.end() &&
                !assignments.empty())
                RETURN ("ERROR: Repeated assignment to symbol ", assign->name);

            /* Rule 2: Inputs cannot have assignments */
            if (symbol_added (&symbol_list, assign->name, INPUT))
                RETURN ("ERROR: Symbol cannot be both assignment and input: ",
                        assign->name);
            assignments[assign->name] = assign;

        } else {
            NWireDeclaration * wire = dynamic_cast<NWireDeclaration*>(*iter);
            retval = wire->visit (context, &exp);
            if (exp != DECL)
                RETURN ("ERROR: Input declaration should have type DECL", "");

            entry = retval.symbol;
            /* Rule 3: Cannot declare a wire the clashes with input/output
             * Rule 5: Cannot repeat a wire declaration */
            if ( symbol_added (&symbol_list, entry->name, WIRE) )
                RETURN ("ERROR: Repeated declaration of symbol ", entry->name);

            symbol_list[entry->name] = WIRE;
            context->lastsym->next = entry;
            context->lastsym = context->lastsym->next;
        }
    }

    /* Link up the OUTPUT and WIRE symtab entries to the assignments */
    for (entry = context->symtab; entry != NULL; entry = entry->next)
    {
        /* Recall rule 2 was enforced above. If an assignment is found, it
         * cannot correspond to an INPUT declaration. Hence, no need to check
         * that here. */
        map<const char *,assign_entry*>::const_iterator iter =
            find_assign (&assignments, entry->name);
        if (iter != assignments.end())
        {
            entry->assign = iter->second;
            assignments.erase(iter->first);
        }
    }

    /* Rule 6: Assignments must have a WIRE or OUTPUT declaration */
    for (map<const char *,assign_entry*>::const_iterator iter = assignments.begin();
            iter != assignments.end(); iter++)
    {
        cerr << "ERROR: " << iter->first <<
            " has assignment but no declaration" << endl;
        context->success = false;
    }
}

/* Handles allocation of a new module for the linked list */
module_t *
next_module (module_t ** first, module_t * current)
{
    module_t * module = (module_t *) malloc (sizeof (module_t));
    if (*first == NULL)
    {
        *first = module;
    } else {
        current->next = module;
    }
    module->symtab = NULL;
    module->name = NULL;
    module->next = NULL;

    return module;
}

/* ************************************************************************* *
 * build_module -- C-style interface to the C++ parser                       *
 *                                                                           *
 * Parameters                                                                *
 *   nmodule - the NModule built by the Bison-generated parser               *
 *   module - the module to be built to represent the module                 *
 *                                                                           *
 * Returns                                                                   *
 *   The built module or NULL if an error occured.                           *
 * ************************************************************************* */
module_t *
build_module (NModule * nmodule, module_t * module)
{
    CodeGenContext context;
    map<const char *, bool> symbols;
    symtab_entry * entry = NULL;
    context.symtab = NULL;
    context.lastsym = NULL;
    context.enttab = NULL;
    context.lastent = NULL;
    context.success = true;

    nmodule->visit (&context);

    if (!context.success)
    {
        free_module (module, symbols);
        return NULL;
    }

    module->name = context.name;
    module->symtab = context.symtab;

    return module;
}

/* ************************************************************************* *
 * free_ast -- Deallocates all memory allocated for the AST                  *
 *                                                                           *
 * Parameters                                                                *
 *   ast - the AST to be free                                                *
 *                                                                           *
 * Returns                                                                   *
 *   none                                                                    *
 *                                                                           *
 * Notes                                                                     *
 *   This also frees up all symbols, so this should only be done once at the *
 *   end of program execution.                                               *
 * ************************************************************************* */
static void
free_module (module_t * module, map<const char *, bool> & symbols)
{
    symtab_entry * symtab;

    symbols[module->name] = true;

    for (symtab = module->symtab; symtab != NULL; symtab = symtab->next)
    {
        if (symbols.find(symtab->name) == symbols.end())
            symbols[symtab->name] = true;
        if (symtab->type != INPUT)
            free_assign (symtab->assign);
    }

    free (module);
}

static void
free_bop (binary_op * bop)
{
    FREE_SWITCH (bop->rtype, bop->rhs);
    FREE_SWITCH (bop->ltype, bop->lhs);
    free ((void*)bop);
}

static void
free_uop (unary_op * uop)
{
    FREE_SWITCH (uop->rtype, uop->rhs);
    free ((void*)uop);
}

static void
free_assign (assign_entry * assign)
{
    FREE_SWITCH (assign->type, assign->eval);
    free ((void*)assign);
}

void
free_ast (ast_t * ast)
{
    module_t * module;
    map<const char *, bool> symbols;
    for (module = ast->modules; module != NULL; module = module->next)
        free_module (module, symbols);

    for (map<const char *, bool>::iterator iter = symbols.begin();
            iter != symbols.end(); iter++)
        free ((void*)(iter->first));

    free (ast);
}

/* ************************************************************************* *
 * parse_file -- C-style interface to the parser                             *
 *                                                                           *
 * Parameters                                                                *
 *   filename - the name of the Verilog source file to compile               *
 *                                                                           *
 * Returns                                                                   *
 *   The abstract syntax tree representation of the file. This tree contains *
 *   a linked list of modules, each of which has its own symbol table and    *
 *   name. The symbol table of each module contains declarations as well as  *
 *   assignments for OUTPUT and WIRE symbols. If an error occurs at any      *
 *   point in the parsing, this function returns NULL.                       *
 *                                                                           *
 * TODO: If one module fails to build, call free_module on any previous      *
 *       modules that were built. Also, delete the NModuleList objects       *
 *       created by the parser. Currently, this is a massive memory leak.    *
 * ************************************************************************* */
ast_t *
parse_file (const char * filename)
{
    map<const char *, bool> symbols;
    ast_t * ast = (ast_t *) malloc (sizeof (ast_t));
    NOT_NULL (ast);
    ast->modules = NULL;
    module_t * module = NULL;
    module_t * tmp = NULL;
    symtab_entry * entry = NULL;

    /* Parse the file passed as input */
    yyin = fopen (filename, "r");
    yyparse ();
    fclose (yyin);

    /* For each Verilog module, create a module in the AST */
    for (ModuleList::const_iterator it = programBlock->modules.begin();
            it != programBlock->modules.end(); it++)
    {
        module = next_module (&ast->modules, module);
        NOT_NULL (module);
        module = build_module ((*it), module);
        if (module == NULL) /* Failed to compile */
        {
            for (tmp = ast->modules; tmp != NULL; tmp = tmp->next)
                if (tmp->next == module)
                {
                    tmp->next = NULL;
                    free (module);
                }
            free_ast (ast);
            cerr << "Failed to build module" << endl;
            return NULL;
        }
    }

    /* Delete the parse structure to prevent memory leaks */
    delete programBlock;

    return ast;
}
