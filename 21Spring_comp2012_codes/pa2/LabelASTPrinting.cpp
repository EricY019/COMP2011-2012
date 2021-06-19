#include "LabelAST.h"

#include <iostream>

#include "InstructionAST.h"
#include "Strings.h"

void LabelAST::print(u32 indent) const {
  std::cout << alignTree(indent)
            << getTokenName()
            << " \""
            << getLabelName()
            << "\"\n";

  for (u32 i = 0; i < getNumInstructions(); ++i) {
    getInstructionByOffset(i)->print(indent + 1);
  }
}
