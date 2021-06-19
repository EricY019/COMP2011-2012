#include "BranchInstructionAST.h"

void BInstructionAST::print(u32 indent) const {
  ExprAST::print(indent);

  mTargetLabel->print(indent + 1);
}

void BlInstructionAST::print(u32 indent) const {
  ExprAST::print(indent);

  mTargetLabel->print(indent + 1);
}

void BxInstructionAST::print(u32 indent) const {
  ExprAST::print(indent);

  mRetAddrReg->print(indent + 1);
}

void CmpInstructionAST::print(u32 indent) const {
  ExprAST::print(indent);

  mRegOperand1->print(indent + 1);
}

void RegCmpInstructionAST::print(u32 indent) const {
  CmpInstructionAST::print(indent);

  mRegOperand2->print(indent + 1);
}

void ImmCmpInstructionAST::print(u32 indent) const {
  CmpInstructionAST::print(indent);

  mImmOperand2->print(indent + 1);
}
