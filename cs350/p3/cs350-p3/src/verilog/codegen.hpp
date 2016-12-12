/* This file is used for parsing the Verilog file. Do NOT change anything here. */
#ifndef __CODEGEN_HPP__
#define __CODEGEN_HPP__

#include <string>
#include "node.h"

/* CodeGenContext is the context for processing an NModule */
class CodeGenContext {
    public:
        const char * name;
        symtab_entry * symtab;
        symtab_entry * lastsym;
        assign_entry * enttab;
        assign_entry * lastent;
        bool success;
};

#endif
