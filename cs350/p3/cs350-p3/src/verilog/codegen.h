/* ************************************************************************* *
 * codegen.h                                                                 *
 * ---------                                                                 *
 *  Author:   Michael S. Kirkpatrick                                         *
 *  Purpose:  This file defines the data structures and types for the AST of *
 *            the Verilog file. See the project description for more info.   *
 * ************************************************************************* */
#ifndef __CODEGEN_H__
#define __CODEGEN_H__

/* Operation types */
typedef enum { NOT, OR, AND, XOR } op_t;

/* Types of expressions - BADEXP is for bad expressions that shouldn't compile */
typedef enum { INT = 10, IDENT, UOP, BOP, ASSIGN, DECL, BADEXP } exp_t;

/* Wire declarations can be input, output, or intermediate */
typedef enum { INPUT = 20, OUTPUT, WIRE } decl_t;

/* The union of types for evaluating an expression */
typedef union {
    long value;                     /* an integer expression */
    const char * name;              /* an identifier */
    struct unary_op * uop;          /* a unary operation - must be NOT */
    struct binary_op * bop;         /* a binary operation - AND, OR, XOR */
    struct assign_entry * assign;   /* an assignment entry (see below) */
    struct symtab_entry * symbol;   /* a symbol table entry (see below) */
} eval_t;

/* Unary operations:
 *   op must be NOT
 *   rhs is the expression being NOTed
 *   rtype is the type of rhs
 * Examples:
 *   ~i0
 *     op = NOT, rhs.name = "i0", rtype = IDENT
 *
 *   ~ (p0 | i0)
 *     op = NOT, rhs.bop->op = OR, rtype = BOP
 */
typedef struct unary_op {
    op_t op;
    eval_t rhs;
    exp_t rtype;
} unary_op;

/* Binary operations:
 *   op must not be NOT
 *   ltype is the type for lhs
 *   rtype is the type for rhs
 * Examples:
 *   i0 & ~p0
 *     op = AND
 *     ltype = IDENT, lhs.name = "i0"
 *     rtype = UOP, rhs.uop->op = NOT, rhs.uop->rtype = IDENT
 */
typedef struct binary_op {
    op_t op;
    eval_t lhs;
    exp_t ltype;
    eval_t rhs;
    exp_t rtype;
} binary_op;

/* Assignment entry:
 *   name is the wire or output being assigned a value
 *   type is the type of the expression being assigned
 *   eval is the appropriate evaluation data structure
 * Examples:
 *   eq = p0 | i0;
 *     name = "eq"
 *     type = BOP
 *     eval.bop->op = OR
 * 
 *   p0 = ~ (i0 ^ (i1 & i2))
 *     name = "p0"
 *     type = UOP
 *     eval.uop->op = NOT
 *     eval.uop->rtype = XOR
 */
typedef struct assign_entry {
    const char * name;
    exp_t type;
    eval_t eval;
} assign_entry;

/* Symbol table entry:
 *   name is the symbol name
 *   type is the type of declaration (input, output, wire)
 *   assign is the assignment entry for outputs and wires
 *     note that the assign->name == name
 *   next is the pointer to the next symbol table entry (linked list)
 * Examples:
 *   wire p0;
 *   p0 = i0 & ~i1
 *     name = "p0"
 *     type = WIRE
 *     assign->type = BOP
 *     assign->name = "p0"
 *     assign->eval.bop->op = AND
 *
 *   input i0;
 *     name = "i0"
 *     type = INPUT
 *     assign = NULL
 */
typedef struct symtab_entry {
    const char * name;
    decl_t type;
    assign_entry * assign;
    struct symtab_entry * next;
} symtab_entry;

/* Verilog module structure:
 *   symtab is the linked list of symbols (inputs, outputs, wires)
 *   name is the name of the module
 *   next is the next module in the Verilog .v file
 */
typedef struct module_t {
    symtab_entry * symtab;
    const char * name;
    struct module_t * next;
} module_t;

/* Abstract syntax tree:
 *   In this language, the AST is just a linked list of modules
 */
typedef struct {
    module_t * modules;
} ast_t;

/* This ifdef is needed because these functions are defined in a C++ file, but
 * they will be called from a C file. This extern acts as the glue. */
#ifdef __cplusplus
extern "C" {
#endif

    /* Pass the name of a Verilog file and get the AST */
    ast_t * parse_file (const char *);

    /* You must manually free the AST when you are done with it */
    void free_ast (ast_t * ast);

#ifdef __cplusplus
}
#endif

#endif
