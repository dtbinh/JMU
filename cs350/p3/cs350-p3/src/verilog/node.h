/* This file is used for parsing the Verilog file. Do NOT change anything here. */

#ifndef __VERILOG_NODE__
#define __VERILOG_NODE__

#include <iostream>
#include <vector>

class CodeGenContext;
class NStatement;
class NWireDeclaration;
class NModule;
class NExpression;

using namespace std;

typedef std::vector<NStatement*> StatementList;
typedef std::vector<NWireDeclaration*> WireList;
typedef std::vector<NModule*> ModuleList;

class Node {
    public:
        virtual ~Node() { }
};

class NExpression : public Node {
    public:
        virtual eval_t visit (exp_t * exp) = 0;
};

class NStatement : public Node {
    public:
        virtual eval_t visit (CodeGenContext * context, exp_t * exp) = 0;
};

class NInteger : public NExpression {
    public:
        long value;
        NInteger (long value) : value (value) { }
        eval_t visit (exp_t * exp);
};

class NIdentifier : public NExpression {
    public:
        const char * name;
        NIdentifier (const char * name) : name (name) { }
        eval_t visit (exp_t * exp);
        /* Do NOT free name here. The AST contains copies of this pointer
         * and it will be freed later. */
};

class NOperator : public NExpression {
    public:
        virtual eval_t visit (exp_t * exp) = 0;
};

class NNotOperator : public NOperator {
    public:
        NExpression * rhs;
        NNotOperator (NExpression * rhs) : rhs (rhs) { }
        virtual eval_t visit (exp_t * exp);
        ~NNotOperator() { delete this->rhs; }
};

class NAndOperator : public NOperator {
    public:
        NExpression * lhs;
        NExpression * rhs;
        NAndOperator (NExpression * lhs, NExpression * rhs) :
            lhs (lhs), rhs (rhs) { }
        virtual eval_t visit (exp_t * exp);
        ~NAndOperator() { delete this->rhs; delete this->lhs; }
};

class NOrOperator : public NOperator {
    public:
        NExpression * lhs;
        NExpression * rhs;
        NOrOperator (NExpression * lhs, NExpression * rhs) :
            lhs (lhs), rhs (rhs) { }
        virtual eval_t visit (exp_t * exp);
        ~NOrOperator() { delete this->rhs; delete this->lhs; }
};

class NXorOperator : public NOperator {
    public:
        NExpression * lhs;
        NExpression * rhs;
        NXorOperator (NExpression * lhs, NExpression * rhs) :
            lhs (lhs), rhs (rhs) { }
        virtual eval_t visit (exp_t * exp);
        ~NXorOperator() { delete this->rhs; delete this->lhs; }
};

class NAssignment : public NStatement {
    public:
        NIdentifier * lhs;
        NExpression * rhs;
        NAssignment (NIdentifier * lhs, NExpression * rhs) :
            lhs (lhs), rhs (rhs) { }
        virtual eval_t visit (CodeGenContext * context, exp_t * exp);
        ~NAssignment() { delete this->rhs; delete this->lhs; }
};

class NBlock : public Node {
    public:
        StatementList statements;
        NBlock () { }
        virtual void visit (CodeGenContext * context);
        ~NBlock() {
            for (StatementList::iterator iter = this->statements.begin();
                    iter != this->statements.end(); iter++)
                delete (*iter);
        }
};

class NWireDeclaration : public NStatement {
    public:
        NIdentifier * id;
        NWireDeclaration (NIdentifier * id) : id (id) { }
        virtual eval_t visit (CodeGenContext * context, exp_t * exp);
        ~NWireDeclaration() { delete this->id; }
};

class NModule : public Node {
    public:
        NIdentifier * id;
        WireList * input;
        WireList * output;
        NBlock * statements;
        NModule (NIdentifier * id, WireList * input, WireList * output, NBlock * statements) :
            id (id), input (input), output (output), statements (statements) { }
        virtual void visit (CodeGenContext * context);
        ~NModule() {
            for (WireList::iterator iter = this->input->begin();
                    iter != this->input->end(); iter++)
                delete (*iter);
            for (WireList::iterator iter = this->output->begin();
                    iter != this->output->end(); iter++)
                delete (*iter);
            delete this->statements;
            delete this->id;
        }
};

class NModuleList : public Node {
    public:
        ModuleList modules;
        virtual void visit (CodeGenContext * context);
        ~NModuleList() {
            for (ModuleList::iterator iter = this->modules.begin();
                    iter != this->modules.end(); iter++)
                delete (*iter);
        }
};


#endif
