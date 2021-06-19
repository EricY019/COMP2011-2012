#include "BranchInstructionAST.h"

#include <limits>

#include "Program.h"
#include "Processor.h"
#include "Register.h"
#include "StatusRegister.h"


#include <iostream>
BInstructionAST::BInstructionAST(LabelOperandExprAST* targetLabel) :
    InstructionAST{Op::B}, mTargetLabel{targetLabel} {}

BInstructionAST::~BInstructionAST() {
  delete mTargetLabel;
}

void BInstructionAST::eval(Processor& processor) const {
  const Program& program = *processor.getProgram();
  const std::string& targetName = mTargetLabel->getLabelName();

  long targetLabelIdx = program.getLabelIndexByName(targetName);
  if (targetLabelIdx >= 0) {
    u32 targetPC = static_cast<u32>(targetLabelIdx) << 16;
    processor.getRegister(Register::PC) = targetPC;
  } else {
    processor.getStatusRegister().mT = true;
  }
}

BConditionalInstructionAST::BConditionalInstructionAST(LabelOperandExprAST* targetLabel) :
    BInstructionAST{targetLabel} {}

void BConditionalInstructionAST::eval(Processor& processor) const {
  if (checkCondition(processor)) {
    BInstructionAST::eval(processor);
  }
}

BeqInstructionAST::BeqInstructionAST(LabelOperandExprAST* targetLabel) :
    BConditionalInstructionAST{targetLabel} {}

bool BeqInstructionAST::checkCondition(const Processor& processor) const {
  return processor.getStatusRegister().mZ;
}

BneInstructionAST::BneInstructionAST(LabelOperandExprAST* targetLabel) :
    BConditionalInstructionAST{targetLabel} {}

bool BneInstructionAST::checkCondition(const Processor& processor) const {
  return !processor.getStatusRegister().mZ;
}

BltInstructionAST::BltInstructionAST(LabelOperandExprAST* targetLabel) :
    BConditionalInstructionAST{targetLabel} {}

bool BltInstructionAST::checkCondition(const Processor& processor) const {
  return processor.getStatusRegister().mN != processor.getStatusRegister().mV;
}

BleInstructionAST::BleInstructionAST(LabelOperandExprAST* targetLabel) :
    BConditionalInstructionAST{targetLabel} {}

bool BleInstructionAST::checkCondition(const Processor& processor) const {
  return processor.getStatusRegister().mZ || (processor.getStatusRegister().mN != processor.getStatusRegister().mV);
}

BgtInstructionAST::BgtInstructionAST(LabelOperandExprAST* targetLabel) :
    BConditionalInstructionAST{targetLabel} {}

bool BgtInstructionAST::checkCondition(const Processor& processor) const {
  return !processor.getStatusRegister().mZ && (processor.getStatusRegister().mN == processor.getStatusRegister().mV);
}

BgeInstructionAST::BgeInstructionAST(LabelOperandExprAST* targetLabel) :
    BConditionalInstructionAST{targetLabel} {}

bool BgeInstructionAST::checkCondition(const Processor& processor) const {
  return processor.getStatusRegister().mN == processor.getStatusRegister().mV;
}

BlInstructionAST::BlInstructionAST(LabelOperandExprAST* targetLabel) :
    InstructionAST{Op::BL}, mTargetLabel{targetLabel} {}

void BlInstructionAST::eval(Processor& processor) const {
  const Program& program = *processor.getProgram();
  const std::string& targetName = mTargetLabel->getLabelName();

  long targetLabelIdx = program.getLabelIndexByName(targetName);
  if (targetLabelIdx >= 0) {
    u32 targetPC = static_cast<u32>(targetLabelIdx) << 16;

    processor.getRegister(Register::LR) = processor.getRegister(Register::PC);
    processor.getRegister(Register::PC) = targetPC;
  } else {
    processor.getStatusRegister().mT = true;
  }
}

BlInstructionAST::~BlInstructionAST() {
  delete mTargetLabel;
}

BxInstructionAST::BxInstructionAST(RegisterOperandExprAST* retAddrReg) :
    InstructionAST{Op::BX}, mRetAddrReg{retAddrReg} {}

BxInstructionAST::~BxInstructionAST() {
  delete mRetAddrReg;
}

void BxInstructionAST::eval(Processor& processor) const {
  processor.getRegister(Register::PC) = processor.getRegister(mRetAddrReg->getRegisterIndex());
}

CmpInstructionAST::CmpInstructionAST(RegisterOperandExprAST* operand1) :
    InstructionAST{Op::CMP}, mRegOperand1{operand1} {}

CmpInstructionAST::~CmpInstructionAST() {
  delete mRegOperand1;
}

void CmpInstructionAST::eval(Processor& processor, u32 op2Value) const {
  u32 op1 = processor.getRegister(getOperand1().getRegisterIndex());

  const u32 result = op1 - op2Value;

  const bool op1Neg = op1 & (1u << 31);
  const bool op2Neg = op2Value & (1u << 31);
  const bool sumNeg = result & (1u << 31);

  processor.getStatusRegister().mN = result & (1u << 31);
  processor.getStatusRegister().mZ = result == 0;
  processor.getStatusRegister().mC = op1 >= op2Value;
  processor.getStatusRegister().mV = (op1Neg != op2Neg && op1Neg != sumNeg);
}

const RegisterOperandExprAST& CmpInstructionAST::getOperand1() const {
  return *mRegOperand1;
}

RegCmpInstructionAST::RegCmpInstructionAST(RegisterOperandExprAST* operand1, RegisterOperandExprAST* operand2) :
    CmpInstructionAST{operand1}, mRegOperand2{operand2} {}

RegCmpInstructionAST::~RegCmpInstructionAST() {
  delete mRegOperand2;
}

void RegCmpInstructionAST::eval(Processor& processor) const {
  u32 op2 = processor.getRegister(mRegOperand2->getRegisterIndex());

  CmpInstructionAST::eval(processor, op2);
}

ImmCmpInstructionAST::ImmCmpInstructionAST(RegisterOperandExprAST* operand1, Imm32OperandExprAST* operand2) :
    CmpInstructionAST{operand1}, mImmOperand2{operand2} {}

void ImmCmpInstructionAST::eval(Processor& processor) const {
  u32 op2 = mImmOperand2->getUnsigned32();

  CmpInstructionAST::eval(processor, op2);
}

ImmCmpInstructionAST::~ImmCmpInstructionAST() {
  delete mImmOperand2;
}