#include "AST.h"

#include <iostream>

#include "Strings.h"

void ExprAST::print(u32 indent) const {
  std::cout << alignTree(indent)
            << getTokenName()
            << '\n';
}
