#include "InstructionAST.h"

void NopInstructionAST::print(u32 indent) const {
  ExprAST::print(indent);
}

void MovInstructionAST::print(u32 indent) const {
  ExprAST::print(indent);

  mDst->print(indent + 1);
}

void RegMovInstructionAST::print(u32 indent) const {
  MovInstructionAST::print(indent);

  mSrc->print(indent + 1);
}

void ImmMovInstructionAST::print(u32 indent) const {
  MovInstructionAST::print(indent);

  mImm->print(indent + 1);
}

void AddInstructionAST::print(u32 indent) const {
  ExprAST::print(indent);

  mDst->print(indent + 1);
  mSrc1->print(indent + 1);
}

void RegAddInstructionAST::print(u32 indent) const {
  AddInstructionAST::print(indent);

  mSrc2->print(indent + 1);
}

void ImmAddInstructionAST::print(u32 indent) const {
  AddInstructionAST::print(indent);

  mImm->print(indent + 1);
}

void SubInstructionAST::print(u32 indent) const {
  ExprAST::print(indent);

  mDst->print(indent + 1);
  mSrc1->print(indent + 1);
}

void RegSubInstructionAST::print(u32 indent) const {
  SubInstructionAST::print(indent);

  mSrc2->print(indent + 1);
}

void ImmSubInstructionAST::print(u32 indent) const {
  SubInstructionAST::print(indent);

  mImm->print(indent + 1);
}

void PushInstructionAST::print(u32 indent) const {
  ExprAST::print(indent);

  mRegList->print(indent + 1);
}

void PopInstructionAST::print(u32 indent) const {
  ExprAST::print(indent);

  mRegList->print(indent + 1);
}

void StrInstructionAST::print(u32 indent) const {
  ExprAST::print(indent);

  mSrc->print(indent + 1);
  mDst->print(indent + 1);
}

void LdrInstructionAST::print(u32 indent) const {
  ExprAST::print(indent);

  mDst->print(indent + 1);
  mSrc->print(indent + 1);
}
