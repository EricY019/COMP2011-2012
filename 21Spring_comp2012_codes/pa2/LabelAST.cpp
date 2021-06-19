#include "LabelAST.h"

#include <vector>

#include "InstructionAST.h"

struct LabelAST::Impl {
  ~Impl();

  std::string mName;
  std::vector<InstructionAST*> mExprs;
};

LabelAST::Impl::~Impl() {
  for (InstructionAST*& expr : mExprs) {
    delete expr;
    expr = nullptr;
  }
}

LabelAST::LabelAST(const std::string& name, InstructionAST** exprs, u32 exprsSize) :
    mImpl{new Impl{name, std::vector<InstructionAST*>{exprs, exprs + exprsSize}}} {}

LabelAST::~LabelAST() {
  delete mImpl;
}

const std::string& LabelAST::getLabelName() const {
  return mImpl->mName;
}

InstructionAST** LabelAST::getInstructions() const {
  return mImpl->mExprs.data();
}

u32 LabelAST::getNumInstructions() const {
  return static_cast<u32>(mImpl->mExprs.size());
}

const InstructionAST* LabelAST::getInstructionByOffset(u32 offset) const {
  if (offset >= getNumInstructions()) {
    return nullptr;
  }

  return mImpl->mExprs[offset];
}
