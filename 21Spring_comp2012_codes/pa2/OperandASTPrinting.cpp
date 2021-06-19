#include "OperandAST.h"

#include <iostream>
#include <iomanip>

#include "Processor.h"
#include "Register.h"
#include "Strings.h"

void IndirectOperandExprAST::print(u32 indent) const {
  ExprAST::print(indent);

  mTarget->print(indent + 1);
  if (mOffset) {
    mOffset->print(indent + 1);
  }
}

void RegisterOperandExprAST::print(u32 indent) const {
  std::cout << alignTree(indent)
            << getTokenName()
            << ' '
            << to_string(static_cast<Register>(mRegister))
            << "\n";
}

void RegisterListOperandExprAST::print(u32 indent) const {
  std::cout << alignTree(indent)
            << getTokenName()
            << '\n';

  for (u8 i = 0; i < 16; ++i) {
    if (hasRegister(i)) {
      RegisterOperandExprAST(i).print(indent + 1);
    }
  }
}

void Imm16OperandExprAST::print(u32 indent) const {
  std::cout << alignTree(indent)
            << getTokenName()
            << " hex:0x"
            << std::hex << std::setfill('0') << std::setw(4) << mValue
            << std::dec << std::setfill(' ') << std::setw(0)
            << " unsigned:"
            << getUnsigned16()
            << " signed:"
            << getSigned16()
            << '\n';
}

void Imm32OperandExprAST::print(u32 indent) const {
  std::cout << alignTree(indent)
            << getTokenName()
            << " hex:0x"
            << std::hex << std::setfill('0') << std::setw(8) << mValue
            << std::dec << std::setfill(' ') << std::setw(0)
            << " unsigned:"
            << getUnsigned32()
            << " signed:"
            << getSigned32()
            << '\n';
}

void LabelOperandExprAST::print(u32 indent) const {
  std::cout << alignTree(indent)
            << getTokenName()
            << " \""
            << getLabelName()
            << "\"\n";
}
