#ifndef AST_H
#define AST_H

#include <string>

#include "Util.h"

// TODO: Write the definition of AST and ExprAST.
class AST{
    public:
    virtual const char * getTokenName() const = 0;
    virtual void print(u32 indent) const = 0;
    virtual ~AST() = default;
};

class ExprAST: public AST{
    public:
    const char * getTokenName() const override = 0;
    void print(u32 indent) const override;
    virtual ~ExprAST() override = default;
};

#endif  // AST_H
