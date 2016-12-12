#ifndef __CANON_STRINGS__
#define __CANON_STRINGS__

const char * STR_CONST[] =
{
    // op_t 0..3
    "~" /* NOT */, "|" /* OR */, "&" /* AND */, "^" /* XOR */,

    // fill 4..9
    "" /* EMPTY */, "" /* EMPTY */, "" /* EMPTY */, 
    "" /* EMPTY */, "" /* EMPTY */, "" /* EMPTY */, 

    // exp_t 10..16
    "INT", "IDENT", "UOP", "BOP", "ASSIGN", "DECL", "BADEXP",

    // fill 17..19
    "" /* EMPTY */, "" /* EMPTY */, "" /* EMPTY */, 

    // decl_t 20..22
    "INPUT", "OUTPUT", "WIRE" 
};

#endif
