#include "InstructionAST.h"

#include <iostream>

#include "OperandAST.h"
#include "Strings.h"

void printParseError(const char* instrName, const char* explanation) {
  std::cout << "Cannot parse " << instrName << " - " << explanation << std::endl;
}

void printParseError(const char* instrName, const std::string& explanation) {
  printParseError(instrName, explanation.c_str());
}

NopInstructionAST* parseNopInstr(const std::string* operands, u32 numOperands) {
  static_cast<void>(operands);

  if (numOperands > 0) {
    printParseError("nop", makeArgNumErrorString(0));
    return nullptr;
  }

  return new NopInstructionAST{};
}

MovInstructionAST* parseMovInstr(const std::string* operands, u32 numOperands) {
  if (numOperands != 2) {
    printParseError("mov", makeArgNumErrorString(2));
    return nullptr;
  }

  RegisterOperandExprAST* dstReg = parseRegisterOp(operands[0]);
  if (!dstReg) {
    printParseError("mov", ERROR_MSG_PREVIOUS);
    return nullptr;
  }

  const char lastOpChar = operands[1][0];
  if (lastOpChar == '#') {
    Imm32OperandExprAST* immReg = parseImm32Op(operands[1]);
    if (!immReg) {
      printParseError("mov", ERROR_MSG_PREVIOUS);
      return nullptr;
    }

    return new ImmMovInstructionAST{dstReg, immReg};
  }

  RegisterOperandExprAST* srcReg = parseRegisterOp(operands[1]);
  if (!srcReg) {
    printParseError("mov", ERROR_MSG_PREVIOUS);
    return nullptr;
  }

  return new RegMovInstructionAST{dstReg, srcReg};
}

AddInstructionAST* parseAddInstr(const std::string* operands, u32 numOperands) {
  if (numOperands != 3) {
    printParseError("add", makeArgNumErrorString(3));
    return nullptr;
  }

  RegisterOperandExprAST* dstReg = parseRegisterOp(operands[0]);
  if (!dstReg) {
    printParseError("add", ERROR_MSG_PREVIOUS);
    return nullptr;
  }

  RegisterOperandExprAST* src1Reg = parseRegisterOp(operands[1]);
  if (!src1Reg) {
    printParseError("add", ERROR_MSG_PREVIOUS);
    return nullptr;
  }

  RegisterOperandExprAST* src2Reg = parseRegisterOp(operands[2]);
  if (src2Reg) {
    return new RegAddInstructionAST{dstReg, src1Reg, src2Reg};
  }

  Imm32OperandExprAST* immReg = parseImm32Op(operands[2]);
  if (immReg) {
    return new ImmAddInstructionAST{dstReg, src1Reg, immReg};
  }

  printParseError("add", "Unknown operand type for third operand");
  return nullptr;
}

SubInstructionAST* parseSubInstr(const std::string* operands, u32 numOperands) {
  if (numOperands != 3) {
    std::cout << "Cannot parse 'sub' instruction - Instruction requires 3 operands" << std::endl;
    return nullptr;
  }

  RegisterOperandExprAST* dstReg = parseRegisterOp(operands[0]);
  if (!dstReg) {
    printParseError("sub", ERROR_MSG_PREVIOUS);
    return nullptr;
  }

  RegisterOperandExprAST* src1Reg = parseRegisterOp(operands[1]);
  if (!src1Reg) {
    printParseError("sub", ERROR_MSG_PREVIOUS);
    return nullptr;
  }

  RegisterOperandExprAST* src2Reg = parseRegisterOp(operands[2]);
  if (src2Reg) {
    return new RegSubInstructionAST{dstReg, src1Reg, src2Reg};
  }

  Imm32OperandExprAST* immReg = parseImm32Op(operands[2]);
  if (immReg) {
    return new ImmSubInstructionAST{dstReg, src1Reg, immReg};
  }

  printParseError("sub", "Unknown operand type for third operand");
  return nullptr;
}

PushInstructionAST* parsePushInstr(const std::string* operands, u32 numOperands) {
  if (numOperands != 1) {
    std::cout << "Cannot parse 'push' instruction - Instruction requires 1 operand" << std::endl;
    return nullptr;
  }

  RegisterListOperandExprAST* regList = parseRegisterListOp(operands[0]);
  if (!regList) {
    printParseError("push", ERROR_MSG_PREVIOUS);
  }

  return new PushInstructionAST{regList};
}

PopInstructionAST* parsePopInstr(const std::string* operands, u32 numOperands) {
  if (numOperands != 1) {
    std::cout << "Cannot parse 'pop' instruction - Instruction requires 1 operand" << std::endl;
    return nullptr;
  }

  RegisterListOperandExprAST* regList = parseRegisterListOp(operands[0]);
  if (!regList) {
    printParseError("pop", ERROR_MSG_PREVIOUS);
  }

  return new PopInstructionAST{regList};
}

StrInstructionAST* parseStrInstr(const std::string* operands, u32 numOperands) {
  if (numOperands != 2) {
    printParseError("str", "Instruction requires 2 operands");
    return nullptr;
  }

  RegisterOperandExprAST* src = parseRegisterOp(operands[0]);
  if (!src) {
    printParseError("str", ERROR_MSG_PREVIOUS);
    return nullptr;
  }

  IndirectOperandExprAST* dst = parseIndirectOp(operands[1]);
  if (!dst) {
    printParseError("str", ERROR_MSG_PREVIOUS);
    return nullptr;
  }

  return new StrInstructionAST{src, dst};
}

LdrInstructionAST* parseLdrInstr(const std::string* operands, u32 numOperands) {
  if (numOperands != 2) {
    printParseError("ldr", "Instruction requires 2 operands");
    return nullptr;
  }

  RegisterOperandExprAST* dst = parseRegisterOp(operands[0]);
  if (!dst) {
    printParseError("ldr", ERROR_MSG_PREVIOUS);
    return nullptr;
  }

  IndirectOperandExprAST* src = parseIndirectOp(operands[1]);
  if (!src) {
    printParseError("ldr", ERROR_MSG_PREVIOUS);
    return nullptr;
  }

  return new LdrInstructionAST{dst, src};
}
