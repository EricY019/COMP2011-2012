#include "OperandAST.h"

#include <climits>
#include <algorithm>
#include <bitset>
#include <iostream>

RegisterOperandExprAST::RegisterOperandExprAST(u8 rx) :
    mRegister{rx} {}

RegisterOperandExprAST::~RegisterOperandExprAST() = default;

Register RegisterOperandExprAST::getRegister() const {
  return static_cast<Register>(mRegister);
}

u8 RegisterOperandExprAST::getRegisterIndex() const {
  return mRegister;
}

RegisterListOperandExprAST::RegisterListOperandExprAST(u16 reglist) :
    mRegList{reglist} {}

u8 RegisterListOperandExprAST::getListCount() const {
  return static_cast<u8>(std::bitset<sizeof(u16) * CHAR_BIT>{mRegList}.count());
}

bool RegisterListOperandExprAST::hasRegister(u8 rx) const {
  if (rx >= 16) {
    std::cerr << "Error: RegisterListOperandExprAST::hasRegister: Index out of bounds (" << rx << ")" << std::endl;

    std::abort();
  }

  return (mRegList & (1 << rx)) > 0;
}

bool RegisterListOperandExprAST::hasRegister(Register reg) const {
  return hasRegister(static_cast<u8>(reg));
}

s16 ImmOperandExprAST::getSigned16() const {
  u16 v = getUnsigned16();
  s16 i;
  std::copy_n(&v, 1, &i);
  return i;
}

s32 ImmOperandExprAST::getSigned32() const {
  u32 v = getUnsigned32();
  s32 i;
  std::copy_n(&v, 1, &i);
  return i;
}

Imm16OperandExprAST::Imm16OperandExprAST(s16 value) :
    mValue{static_cast<u16>(value)} {}

u16 Imm16OperandExprAST::getUnsigned16() const {
  return mValue;
}

u32 Imm16OperandExprAST::getUnsigned32() const {
  return getUnsigned16();
}

Imm32OperandExprAST::Imm32OperandExprAST(s32 value) :
    mValue{static_cast<u32>(value)} {}

u16 Imm32OperandExprAST::getUnsigned16() const {
  return static_cast<u16>(mValue & ((1u << 16) - 1));
}

u32 Imm32OperandExprAST::getUnsigned32() const {
  return mValue;
}

IndirectOperandExprAST::IndirectOperandExprAST(RegisterOperandExprAST* target, ImmOperandExprAST* offset) :
    mTarget{target}, mOffset{offset} {}

IndirectOperandExprAST::~IndirectOperandExprAST() {
  delete mOffset;
  delete mTarget;
}

RegisterOperandExprAST& IndirectOperandExprAST::getRegisterTarget() const {
  return *mTarget;
}

s16 IndirectOperandExprAST::getOffset() const {
  return mOffset ? mOffset->getSigned16() : 0;
}
LabelOperandExprAST::LabelOperandExprAST(const std::string& name) :
    mName{name} {}

const std::string& LabelOperandExprAST::getLabelName() const {
  return mName;
}
