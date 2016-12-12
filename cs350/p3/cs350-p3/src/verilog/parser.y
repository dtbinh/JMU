/* This file is used for parsing the Verilog file. Do NOT change anything here. */
%{
#include "codegen.h"
#include "codegen.hpp"
NModuleList * programBlock;

extern int yylex();
void yyerror (const char *s) { cout << "ERROR: " << s << endl; }

%}

/* Define the possible types of syntactical structures */
%union {
    Node *node;
    NBlock *block;
    NExpression *expr;
    NIdentifier *ident;
    NInteger *number;
    NModule *module;
    NWireDeclaration *wiredec;
    NStatement *stmt;
    std::vector<NWireDeclaration*> *wirevec;
    NModuleList *modvec;
    char *string;
    int token;
}

/* Associate token types with syntax types */
%token <string> TIDENTIFIER TINTEGER
%token <token> TMODULE TENDMODULE TINPUT TOUTPUT TWIRE TASSIGN
%token <token> TLPAREN TRPAREN TSEMI
%token <token> TXOR TNOT TAND TOR TEQUAL

/* Assign types to the semantic actions */
%type <ident> ident
%type <expr> expr
%type <wirevec> modinput modoutput
%type <module> module
%type <modvec> circuit modules
%type <stmt> stmt wiredec assign
%type <block> stmts
%type <number> numeric

/* NOT has higher precedence than XOR, AND, and OR */
%left TNOT
%left TXOR TAND TOR

/* Specify the entry point for the context-free grammar */
%start circuit

/* What follows from here is the context-free grammar for our Verilog subset.
 * Read this only if you are interested in programming language theory. */

%%

circuit : modules { programBlock = $1; }
        ;

modules : module { $$ = new NModuleList(); $$->modules.push_back ($<module>1); }
        | modules module { $1->modules.push_back ($<module>2); }
        ;

module : TMODULE ident TLPAREN modinput modoutput TRPAREN TSEMI stmts TENDMODULE { $$ = new NModule($2, $4, $5, $8); }
       ;

modinput : /* empty */ { $$ = new WireList(); }
         | TINPUT wiredec { $$ = new WireList(); $$->push_back($<wiredec>2); }
         | modinput TINPUT wiredec { $$->push_back($<wiredec>3); }
         ;

modoutput : TOUTPUT wiredec { $$ = new WireList(); $$->push_back($<wiredec>2); }
          | modoutput TOUTPUT wiredec { $$->push_back($<wiredec>3); }
          ;

ident : TIDENTIFIER { $$ = new NIdentifier ($1); }
      ;

wiredec : TWIRE ident { $$ = new NWireDeclaration($2); }
        ;

numeric : TINTEGER { $$ = new NInteger (atol ($1)); }
        ;

stmts : /* empty */ { $$ = new NBlock(); }
      | stmt { $$ = new NBlock(); $$->statements.push_back($<stmt>1); }
      | stmts stmt { $1->statements.push_back($<stmt>2); }
      ;

stmt : wiredec TSEMI
     | assign TSEMI
     ;

assign : TASSIGN ident TEQUAL expr { $$ = new NAssignment ($2, $4); }
       ;

expr : ident { $<ident>$ = $1; }
     | TNOT expr { $$ = new NNotOperator ($2); }
     | expr TAND expr { $$ = new NAndOperator ($1, $3); }
     | expr TOR expr { $$ = new NOrOperator ($1, $3); }
     | expr TXOR expr { $$ = new NXorOperator ($1, $3); }
     | TLPAREN expr TRPAREN { $$ = $2; }
     | numeric { $<number>$ = $1; }
     ;

%%
