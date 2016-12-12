/* This file is used for parsing the Verilog file. Do NOT change anything here. */
%{
#include "codegen.h"
#include "codegen.hpp"
#include "parser.hpp"

char *
lookup_identifier (char * text)
{
    char * str = NULL;
    static vector<char *>names;
    for (vector<char *>::iterator iter = names.begin();
            iter != names.end(); iter++)
        if (!strcmp(*iter, text)) return *iter;
    str = (char *) malloc (strlen (text) + 1);
    strncpy (str, text, strlen (text) + 1);
    names.push_back (str);
    return str;
}


/* C macros for saving tokens or returning a token type */
#define SAVE_TOKEN yylval.string = lookup_identifier (yytext)
#define TOKEN(t) (yylval.token = t)
extern "C" int yywrap () { return 1; }
using namespace std;

%}

/* What follow from here is the regular expression representation of tokens in
 * our Verilog subset. This information is used by flex to create the
 * appropriate tokens that bison will use as input. */

%%

[ \t\n]                     ;
"module"                    return TOKEN(TMODULE);
"input"                     return TOKEN(TINPUT);
"output"                    return TOKEN(TOUTPUT);
"wire"                      return TOKEN(TWIRE);
"assign"                    return TOKEN(TASSIGN);
"endmodule"                 return TOKEN(TENDMODULE);
"("                         return TOKEN(TLPAREN);
")"                         return TOKEN(TRPAREN);
";"                         return TOKEN(TSEMI);
"^"                         return TOKEN(TXOR);
"~"                         return TOKEN(TNOT);
"&"                         return TOKEN(TAND);
"|"                         return TOKEN(TOR);
"="                         return TOKEN(TEQUAL);
[a-zA-Z_][a-zA-Z0-9_]*      SAVE_TOKEN; return TIDENTIFIER;
[0-9]+                      SAVE_TOKEN; return TINTEGER;
.                           cerr << "Unknown token: " << yytext << endl; yyterminate();

%%
