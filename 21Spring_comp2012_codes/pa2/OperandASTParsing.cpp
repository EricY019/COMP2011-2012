#include "OperandAST.h"

#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

#include "Strings.h"

RegisterOperandExprAST* parseRegisterOp(const std::string& operand) {
  if (operand.empty()) {
    return nullptr;
  }

  if (operand == "sp") {
    return new RegisterOperandExprAST{13};
  }
  if (operand == "lr") {
    return new RegisterOperandExprAST{14};
  }
  if (operand == "pc") {
    return new RegisterOperandExprAST{15};
  }

  if (operand.front() != 'r') {
    return nullptr;
  }

  unsigned long regNum = std::stoul(operand.substr(1));
  if (regNum >= 16) {
    std::cout << "Cannot parse Register Expression " << operand << " - Register Number out of range" << std::endl;
    return nullptr;
  }

  return new RegisterOperandExprAST{static_cast<u8>(regNum)};
}

RegisterListOperandExprAST* parseRegisterListOp(const std::string& operand) {
  if (operand.front() != '{' || operand.back() != '}') {
    std::cout << "Cannot parse Indirect Operand - Operand must start with [ and end with ]" << std::endl;
    return nullptr;
  }

  u32 numOperands = 0;
  std::string* operands = parseSubExprOperands(operand.substr(1, operand.size() - 2), numOperands);

  if (numOperands == 0) {
    std::cout << "Cannot parse RegList Operand - Operand must have at least 1 nested operand" << std::endl;
  }

  u16 regListMask = 0;
  for (std::size_t i = 0; i < numOperands; ++i) {
    const std::string& rOp = operands[i];

    RegisterOperandExprAST* reg = parseRegisterOp(rOp);
    if (!reg) {
      std::cout << "Cannot parse RegList Operand - See previous error" << std::endl;

      delete operands;
      return nullptr;
    }

    regListMask |= static_cast<u16>(1u << reg->getRegisterIndex());
    delete reg;
  }

  delete[] operands;
  return new RegisterListOperandExprAST{regListMask};
}

Imm16OperandExprAST* parseImm16Op(const std::string& operand) {
  if (operand.front() != '#') {
    std::cout << "Cannot parse Const Operand - Operand must start with '#'" << std::endl;
    return nullptr;
  }

  long long numVal = std::stoll(operand.substr(1));
  if (numVal > std::numeric_limits<u16>::max() || numVal < std::numeric_limits<s16>::min()) {
    std::cout << "Operand value ("
              << numVal
              << ") exceeds 16-bit value; Taking lower 16-bits" << std::endl;
    numVal = static_cast<long long>(static_cast<unsigned long long>(numVal) & std::numeric_limits<u16>::max());
  }
  return new Imm16OperandExprAST{static_cast<s16>(numVal)};
}

Imm32OperandExprAST* parseImm32Op(const std::string& operand) {
  if (operand.front() != '#') {
    std::cout << "Cannot parse Const Operand - Operand must start with '#'" << std::endl;
    return nullptr;
  }

  long long numVal = std::stoll(operand.substr(1));
  if (numVal > std::numeric_limits<u32>::max() || numVal < std::numeric_limits<s32>::min()) {
    std::cout << "Operand value ("
              << numVal
              << ") exceeds 32-bit value; Taking lower 32-bits" << std::endl;
    numVal = static_cast<long long>(static_cast<unsigned long long>(numVal) & std::numeric_limits<u32>::max());
  }
  return new Imm32OperandExprAST{static_cast<s32>(numVal)};
}

IndirectOperandExprAST* parseIndirectOp(const std::string& operand) {
  if (operand.front() != '[' || operand.back() != ']') {
    std::cout << "Cannot parse Indirect Operand - Operand must start with [ and end with ]" << std::endl;
    return nullptr;
  }

  std::stringstream ss{operand.substr(1, operand.size() - 2)};
  std::vector<std::string> operands;
  while (!ss.eof()) {
    int c = ss.peek();
    std::string temp;

    if (c == '/' || c == '%') {
      break;
    }

    if (std::isspace(c) || c == ',') {
      ss.ignore();
      continue;
    }

    std::getline(ss, temp, ',');

    temp = trimWord(temp);

    if (!temp.empty()) {
      operands.emplace_back(temp);
    }
  }

  if (operands.empty() || operands.size() > 2) {
    std::cout << "Cannot parse Indirect Operand - Operand must have either 1 or 2 nested operands" << std::endl;
  }

  RegisterOperandExprAST* baseReg = parseRegisterOp(operands[0]);
  if (!baseReg) {
    std::cout << "Cannot parse Indirect Operand - See previous error" << std::endl;
    return nullptr;
  }

  ImmOperandExprAST* offset = nullptr;
  if (operands.size() == 2) {
    offset = parseImm16Op(operands[1]);
    if (!offset) {
      std::cout << "Cannot parse Indirect Operand - see previous error" << std::endl;
      return nullptr;
    }
  }

  return new IndirectOperandExprAST{baseReg, offset};
}

LabelOperandExprAST* parseLabelOp(const std::string& operand) {
  return new LabelOperandExprAST{operand};
}
