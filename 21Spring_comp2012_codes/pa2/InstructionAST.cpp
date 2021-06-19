// Theis work belongs to YANG Jingwen, SID: 20677029. All rights reserved.
#include "InstructionAST.h"

#include <algorithm>

#include "MemStack.h"
#include "Processor.h"

InstructionAST::InstructionAST(Op op): mOp(op){
  // TODO: Initialize all members of this class
}

NopInstructionAST::NopInstructionAST(): InstructionAST(Op::NOP) {
  // TODO: Initialize the base class and all members of this class
}

void NopInstructionAST::eval(Processor& processor) const {
  // TODO: Do nothing
  static_cast<void>(processor);
}

MovInstructionAST::MovInstructionAST(RegisterOperandExprAST* dst): InstructionAST(Op::MOV), mDst(dst){
  // TODO: Initialize the base class and all members of this class
  //       Note that:
  //       - The ownership of `dst` is transferred into this class.
  //       - `dst` is never nullptr.
}

MovInstructionAST::~MovInstructionAST() {
  // TODO: Clean up the Expression ASTs owned by this class
  delete mDst; mDst = nullptr;
}

const RegisterOperandExprAST& MovInstructionAST::getDst() const {
  // TODO: You can assume mDst is never nullptr.
  return *mDst;
}

RegMovInstructionAST::RegMovInstructionAST(RegisterOperandExprAST* dst, RegisterOperandExprAST* src): MovInstructionAST(dst), mSrc(src){
  // TODO: Initialize the base class and all members of this class
  //       Note that the ownership of dst and src is transferred into this class.
}

RegMovInstructionAST::~RegMovInstructionAST() {
  // TODO: Clean up the Expression ASTs owned by this class
  delete mSrc; mSrc = nullptr;
}

void RegMovInstructionAST::eval(Processor& processor) const {
  // TODO: Implement register-to-register move
  processor.getRegister(getDst().getRegister()) = processor.getRegister(mSrc->getRegister());
}

ImmMovInstructionAST::ImmMovInstructionAST(RegisterOperandExprAST* dst, Imm32OperandExprAST* imm): MovInstructionAST(dst), mImm(imm){
  // TODO: Initialize the base class and all members of this class
  //       Note that:
  //       - The ownership of `dst` and `imm` is transferred into this class.
  //       - `dst` and `imm` is never nullptr.
}

ImmMovInstructionAST::~ImmMovInstructionAST() {
  // TODO: Clean up the Expression ASTs owned by this class
  delete mImm; mImm = nullptr;
}

void ImmMovInstructionAST::eval(Processor& processor) const {
  // TODO: Implement immediate-to-register move
  processor.getRegister(getDst().getRegister()) = mImm->getUnsigned32();
}

AddInstructionAST::AddInstructionAST(RegisterOperandExprAST* dst, RegisterOperandExprAST* src1): InstructionAST(Op::ADD), mDst(dst), mSrc1(src1){
  // TODO: Initialize the base class and all members of this class
  //       Note that:
  //       - The ownership of `dst` and `src1` is transferred into this class.
  //       - `dst` and `src1` is never nullptr.
}

AddInstructionAST::~AddInstructionAST() {
  // TODO: Clean up the Expression ASTs owned by this class
  delete mDst; mDst = nullptr;
  delete mSrc1; mSrc1 = nullptr;
}

const RegisterOperandExprAST& AddInstructionAST::getDst() const {
  // TODO: You can assume mDst is never nullptr.
  return *mDst;
}

const RegisterOperandExprAST& AddInstructionAST::getSrc1() const {
  // TODO: You can assume mSrc1 is never nullptr.
  return *mSrc1;
}

RegAddInstructionAST::RegAddInstructionAST(RegisterOperandExprAST* dst,
                                           RegisterOperandExprAST* src1,
                                           RegisterOperandExprAST* src2):
                                           AddInstructionAST(dst, src1),
                                           mSrc2(src2){
  // TODO: Initialize the base class and all members of this class
  //       Note that:
  //       - The ownership of `dst`, `src1` and `src2` is transferred into this class.
  //       - `dst`, `src1` and `src2` is never nullptr.
}

RegAddInstructionAST::~RegAddInstructionAST() {
  // TODO: Clean up the Expression ASTs owned by this class
  delete mSrc2; mSrc2 = nullptr;
}

void RegAddInstructionAST::eval(Processor& processor) const {
  // TODO: Implement register-register add
  //       Note that:
  //       The addition should wraparound if it overflows. In other words, if the result of the addition does not fit 
  //       into the register, take the lower 32-bits of the result.
  //       For example, 4294967295 (i.e. maximum number represented by u32) + 1 = 0
  processor.getRegister(getDst().getRegister()) = static_cast<u32>(processor.getRegister(getSrc1().getRegister())) + static_cast<u32>(processor.getRegister(mSrc2->getRegister()));
}

ImmAddInstructionAST::ImmAddInstructionAST(RegisterOperandExprAST* dst,
                                           RegisterOperandExprAST* src,
                                           Imm32OperandExprAST* imm):
                                           AddInstructionAST(dst, src),
                                           mImm(imm) {
  // TODO: Initialize the base class and all members of this class
  //       Note that:
  //       - The ownership of `dst`, `src` and `imm` is transferred into this class.
  //       - `dst`, `src` and `imm` is never nullptr.
}

ImmAddInstructionAST::~ImmAddInstructionAST() {
  // TODO: Clean up the Expression ASTs owned by this class
  delete mImm; mImm = nullptr;
}

void ImmAddInstructionAST::eval(Processor& processor) const {
  // TODO: Implement register-immediate add
  //       The addition should wraparound if it overflows. In other words, if the result of the addition does not fit 
  //       into the register, take the lower 32-bits of the result.
  //       For example, 4294967295 (i.e. maximum number represented by u32) + 1 = 0
  processor.getRegister(getDst().getRegister()) = static_cast<u32>(processor.getRegister(getSrc1().getRegister())) + mImm->getUnsigned32();
}

SubInstructionAST::SubInstructionAST(RegisterOperandExprAST* dst, RegisterOperandExprAST* src1): InstructionAST(Op::SUB), mDst(dst), mSrc1(src1){
  // TODO: Initialize the base class and all members of this class
  //       Note that:
  //       - The ownership of `dst` and `src1` is transferred into this class.
  //       - `dst` and `src1` is never nullptr.
}

SubInstructionAST::~SubInstructionAST() {
  // TODO: Clean up the Expression ASTs owned by this class
  delete mDst; mDst = nullptr;
  delete mSrc1; mSrc1 = nullptr;
}

const RegisterOperandExprAST& SubInstructionAST::getDst() const {
  // TODO:
  return *mDst;
}

const RegisterOperandExprAST& SubInstructionAST::getSrc1() const {
  // TODO
  return *mSrc1;
}

RegSubInstructionAST::RegSubInstructionAST(RegisterOperandExprAST* dst,
                                           RegisterOperandExprAST* src1,
                                           RegisterOperandExprAST* src2):
                                           SubInstructionAST(dst, src1),
                                           mSrc2(src2){
  // TODO: Initialize the base class and all members of this class
  //       - The ownership of `dst`, `src1` and `src2` is transferred into this class.
  //       Note that:
  //       - `dst`, `src1` and `src2` is never nullptr.
}

void RegSubInstructionAST::eval(Processor& processor) const {
  // TODO: Implement register-register subtraction
  //       The subtraction should wraparound if it overflows.
  //       For example, 0 (i.e. minimum number represented by u32) - 1 = 4294967295
  //       This will also work for signed operands.
  processor.getRegister(getDst().getRegister()) = static_cast<u32>(processor.getRegister(getSrc1().getRegister())) - static_cast<u32>(processor.getRegister(mSrc2->getRegister()));
}

RegSubInstructionAST::~RegSubInstructionAST() {
  // TODO: Clean up the Expression ASTs owned by this class
  delete mSrc2; mSrc2 = nullptr;
}

ImmSubInstructionAST::ImmSubInstructionAST(RegisterOperandExprAST* dst,
                                           RegisterOperandExprAST* src,
                                           Imm32OperandExprAST* imm):
                                           SubInstructionAST(dst, src),
                                           mImm(imm){
  // TODO: Initialize the base class and all members of this class
  //       Note that:
  //       - The ownership of `dst`, `src` and `imm` is transferred into this class.
  //       - `dst`, `src` and `imm` is never nullptr.
}

void ImmSubInstructionAST::eval(Processor& processor) const {
  // TODO: Implement register-immediate subtraction
  //       The subtraction should wraparound if it overflows.
  //       For example, 0 (i.e. minimum number represented by u32) - 1 = 4294967295
  //       This will also work for signed operands.
  processor.getRegister(getDst().getRegister()) = static_cast<u32>(processor.getRegister(getSrc1().getRegister())) - mImm->getUnsigned32();
}

ImmSubInstructionAST::~ImmSubInstructionAST() {
  // TODO: Clean up the Expression ASTs owned by this class
  delete mImm; mImm = nullptr;
}

PushInstructionAST::PushInstructionAST(RegisterListOperandExprAST* regList): InstructionAST(Op::PUSH), mRegList(regList) {
  // TODO: Initialize the base class and all members of this class
  //       Note that:
  //       - The ownership of `regList` is transferred into this class.
  //       - `regList` is never nullptr.
}

PushInstructionAST::~PushInstructionAST() {
  // TODO: Clean up the Expression ASTs owned by this class
  delete mRegList; mRegList = nullptr;
}

void PushInstructionAST::eval(Processor& processor) const {
  // TODO: Implement pushing registers into the stack
  //       Note that:
  //       - You will need to shift the stack pointer (Register::SP) to make room for the contents of the register.
  //       - The stack grows from top to bottom.
  //       - Lower-indexed registers must be stored in lower memory addresses.
  //       - Do NOT store the contents of the register beyond the stack pointer. This will be equivalent to reading 
  //         from an out-of-bounds element in an array!
  //       - The `addr` parameter of `MemStack::store` is in bytes. Registers are 32-bit, so you may need to do some
  //         calculations
  for (int i = 15; i >= 0; i--){
    if (mRegList->hasRegister(static_cast<Register>(i))){
      processor.getRegister(Register::R13) -= static_cast<u32>(4);
      processor.getStack().store(processor.getRegister(static_cast<Register>(i)), processor.getRegister(Register::R13));
    }
  }
}

PopInstructionAST::PopInstructionAST(RegisterListOperandExprAST* regList): InstructionAST(Op::POP), mRegList(regList){
  // TODO: Initialize the base class and all members of this class
  //       Note that:
  //       - The ownership of `regList` is transferred into this class.
  //       - `regList` is never nullptr.
}

PopInstructionAST::~PopInstructionAST() {
  // TODO: Clean up the Expression ASTs owned by this class
  delete mRegList; mRegList = nullptr;
}

void PopInstructionAST::eval(Processor& processor) const {
  // TODO: Implement popping registers from the stack
  //       Note that:
  //       - You will need to shift the stack pointer (Register::SP) to free up room for the registers you have popped.
  //       - The stack shrinks from bottom to top.
  //       - Lower-indexed registers must be loaded from lower memory addresses.
  //       - Do NOT load the contents of the register beyond the stack pointer. This will be equivalent to reading 
  //         from an out-of-bounds element in an array!
  //       - The `addr` parameter of `MemStack::load` is in bytes. Registers are 32-bit, so you may need to do some
  //         calculations.
  for (int i = 0; i <= 15; i++){
    if (mRegList->hasRegister(static_cast<Register>(i))){
      processor.getRegister(static_cast<Register>(i)) = processor.getStack().load(processor.getRegister(Register::R13));
      processor.getRegister(Register::R13) += static_cast<u32>(4);
    }
  }
}

StrInstructionAST::StrInstructionAST(RegisterOperandExprAST* src, IndirectOperandExprAST* dst): InstructionAST(Op::STR), mSrc(src), mDst(dst){
  // TODO: Initialize the base class and all members of this class
  //       Note that:
  //       - The ownership of `dst` and `src` is transferred into this class.
  //       - `dst` and `src` is never nullptr.
}

StrInstructionAST::~StrInstructionAST() {
  // TODO: Clean up the Expression ASTs owned by this class
  delete mSrc; mSrc = nullptr;
  delete mDst; mDst = nullptr;
}

void StrInstructionAST::eval(Processor& processor) const {
  // TODO: Implement storing a single register into the stack
  //       Note that:
  //       - You will need to apply the offset of the indirect operand to the memory address.
  //       - You do not need to shift the stack pointer.
  u32 srcval = processor.getRegister(mSrc->getRegister());
  u32 addr = processor.getRegister(mDst->getRegisterTarget().getRegister()) + static_cast<u32>(mDst->getOffset());
  processor.getStack().store(srcval, addr);
}

LdrInstructionAST::LdrInstructionAST(RegisterOperandExprAST* dst, IndirectOperandExprAST* src): InstructionAST(Op::LDR), mDst(dst), mSrc(src){
  // TODO: Initialize the base class and all members of this class
  //       Note that:
  //       - The ownership of `dst` and `src` is transferred into this class.
  //       - `dst` and `src` is never nullptr.
}

LdrInstructionAST::~LdrInstructionAST() {
  // TODO: Clean up the Expression ASTs owned by this class
  delete mSrc; mSrc = nullptr;
  delete mDst; mDst = nullptr;
}

void LdrInstructionAST::eval(Processor& processor) const {
  // TODO: Implement loading a single register from the stack
  //       Note that:
  //       - You will need to apply the offset of the indirect operand to the memory address.
  //       - You do not need to shift the stack pointer.
  u32 addr = processor.getRegister(mSrc->getRegisterTarget().getRegister()) + static_cast<u32>(mSrc->getOffset());
  u32 srcval = processor.getStack().load(addr);
  processor.getRegister(mDst->getRegister()) = srcval;
}
// This work belongs to YANG Jingwen, SID: 20677029. All rights reserved.