#include "BranchInstructionAST.h"

#include "Strings.h"

BInstructionAST* parseBInstr(const std::string* operands, u32 numOperands) {
  if (numOperands != 1) {
    printParseError("b", "Instruction requires 1 operand");
    return nullptr;
  }

  LabelOperandExprAST* label = parseLabelOp(operands[0]);
  return new BInstructionAST{label};
}

BeqInstructionAST* parseBeqInstr(const std::string* operands, u32 numOperands) {
  if (numOperands != 1) {
    printParseError("beq", "Instruction requires 1 operand");
    return nullptr;
  }

  LabelOperandExprAST* label = parseLabelOp(operands[0]);
  return new BeqInstructionAST{label};
}

BneInstructionAST* parseBneInstr(const std::string* operands, u32 numOperands) {
  if (numOperands != 1) {
    printParseError("bne", "Instruction requires 1 operand");
    return nullptr;
  }

  LabelOperandExprAST* label = parseLabelOp(operands[0]);
  return new BneInstructionAST{label};
}

BltInstructionAST* parseBltInstr(const std::string* operands, u32 numOperands) {
  if (numOperands != 1) {
    printParseError("blt", "Instruction requires 1 operand");
    return nullptr;
  }

  LabelOperandExprAST* label = parseLabelOp(operands[0]);
  return new BltInstructionAST{label};
}

BleInstructionAST* parseBleInstr(const std::string* operands, u32 numOperands) {
  if (numOperands != 1) {
    printParseError("ble", "Instruction requires 1 operand");
    return nullptr;
  }

  LabelOperandExprAST* label = parseLabelOp(operands[0]);
  return new BleInstructionAST{label};
}

BgtInstructionAST* parseBgtInstr(const std::string* operands, u32 numOperands) {
  if (numOperands != 1) {
    printParseError("bgt", "Instruction requires 1 operand");
    return nullptr;
  }

  LabelOperandExprAST* label = parseLabelOp(operands[0]);
  return new BgtInstructionAST{label};
}

BgeInstructionAST* parseBgeInstr(const std::string* operands, u32 numOperands) {
  if (numOperands != 1) {
    printParseError("bge", "Instruction requires 1 operand");
    return nullptr;
  }

  LabelOperandExprAST* label = parseLabelOp(operands[0]);
  return new BgeInstructionAST{label};
}

BlInstructionAST* parseBlInstr(const std::string* operands, u32 numOperands) {
  if (numOperands != 1) {
    printParseError("bl", "Instruction requires 1 operand");
    return nullptr;
  }

  LabelOperandExprAST* label = parseLabelOp(operands[0]);
  return new BlInstructionAST{label};
}

BxInstructionAST* parseBxInstr(const std::string* operands, u32 numOperands) {
  if (numOperands != 1) {
    printParseError("bx", "Instruction requires 1 operand");
    return nullptr;
  }

  RegisterOperandExprAST* retAddrReg = parseRegisterOp(operands[0]);
  if (!retAddrReg) {
    printParseError("bx", ERROR_MSG_PREVIOUS);
    return nullptr;
  }

  return new BxInstructionAST{retAddrReg};
}

CmpInstructionAST* parseCmpInstr(const std::string* operands, u32 numOperands) {
  if (numOperands != 2) {
    printParseError("cmp", "Instruction requires 2 operands");
    return nullptr;
  }

  RegisterOperandExprAST* op1Reg = parseRegisterOp(operands[0]);
  if (!op1Reg) {
    printParseError("cmp", ERROR_MSG_PREVIOUS);
    return nullptr;
  }

  RegisterOperandExprAST* op2Reg = parseRegisterOp(operands[1]);
  if (op2Reg) {
    return new RegCmpInstructionAST{op1Reg, op2Reg};
  }

  Imm32OperandExprAST* op2Imm = parseImm32Op(operands[1]);
  if (op2Imm) {
    return new ImmCmpInstructionAST{op1Reg, op2Imm};
  }

  printParseError("cmp", "Unknown operand type for third operand");
  return nullptr;
}
