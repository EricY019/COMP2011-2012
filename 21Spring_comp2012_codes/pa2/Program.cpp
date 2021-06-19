#include "Program.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <vector>

#include "InstructionASTParsing.h"
#include "LabelAST.h"
#include "Strings.h"

namespace {
constexpr std::array<char, 3> commentChars = {
    '/',
    '%',
    '@'
};
}  // namespace

struct Program::Impl {
  ~Impl();

  bool mIsValid = false;
  std::vector<LabelAST*> mLabels;
};

Program::Impl::~Impl() {
  for (LabelAST*& label : mLabels) {
    delete label;
    label = nullptr;
  }
}

Program::Program(const std::string& program) :
    mImpl{new Impl{}} {
  u32 pos = 0;
  while (pos < program.size()) {
    LabelAST* label = parseLabel(program, pos);
    mImpl->mLabels.emplace_back(label);
  }
  verifyProgram();
}

Program::~Program() {
  delete mImpl;
}

long Program::getLabelIndexByName(const std::string& name) const {
  const std::vector<LabelAST*>::const_iterator it = std::find_if(
      mImpl->mLabels.cbegin(),
      mImpl->mLabels.cend(),
      [&name](const LabelAST* const f) {
        return f->getLabelName() == name;
      });

  if (it != mImpl->mLabels.end()) {
    return std::distance(mImpl->mLabels.cbegin(), it);
  } else {
    return -1;
  }
}

long Program::getLabelIndexByLabel(const LabelAST* label) const {
  const std::vector<LabelAST*>::const_iterator it = std::find(
      mImpl->mLabels.cbegin(),
      mImpl->mLabels.cend(),
      label);

  if (it != mImpl->mLabels.end()) {
    return std::distance(mImpl->mLabels.cbegin(), it);
  } else {
    return -1;
  }
}

const LabelAST* Program::getLabelByIndex(u32 index) const {
  if (index >= mImpl->mLabels.size()) {
    return nullptr;
  }

  return mImpl->mLabels[index];
}

const LabelAST* Program::getLabelByName(const std::string& name) const {
  const std::vector<LabelAST*>::const_iterator it = std::find_if(
      mImpl->mLabels.cbegin(),
      mImpl->mLabels.cend(),
      [&name](const LabelAST* const f) {
        return f->getLabelName() == name;
      });

  if (it != mImpl->mLabels.end()) {
    return *it;
  } else {
    return nullptr;
  }
}

bool Program::isValid() const {
  return mImpl->mIsValid;
}

LabelAST* Program::parseLabel(const std::string& input, u32& pos) {
  if (input.empty()) {
    pos = std::numeric_limits<u32>::max();
    return nullptr;
  }

  std::stringstream ss{input.substr(pos)};

  std::string line;
  std::string funcName;
  std::vector<InstructionAST*> exprs;
  while (std::getline(ss, line)) {
    std::string trimmedLine = trimLine(line);

    if (trimmedLine.empty()) {
      continue;
    }

    char c = trimmedLine.front();
    if (std::find(commentChars.begin(), commentChars.end(), c) != commentChars.end()) {
      continue;
    }

    if (trimmedLine.back() == ':') {
      if (funcName.empty()) {
        funcName = trimmedLine.substr(0, trimmedLine.find_last_of(':'));
        continue;
      } else {
        break;
      }
    }

    exprs.emplace_back(parseInstruction(line));
  }

  if (funcName.empty() || exprs.empty()) {
    pos = std::numeric_limits<u32>::max();
    return nullptr;
  } else if (!ss) {
    pos = std::numeric_limits<u32>::max();
  } else {
    pos += (static_cast<u32>(ss.tellg()) - static_cast<u32>(line.size()) - 1);
  }

  return new LabelAST{funcName, exprs.data(), static_cast<u32>(exprs.size())};
}

void Program::printAST() const {
  for (LabelAST* label : mImpl->mLabels) {
    label->print(0);
    std::cout << std::endl;
  }
}

InstructionAST* Program::parseInstruction(const std::string& input) {
  std::stringstream ss{input};
  std::string instr;

  while (ss.peek() == ' ') {
    ss.ignore();
  }
  std::getline(ss, instr, ' ');

  std::vector<std::string> operands;
  while (!ss.eof()) {
    int c = ss.peek();
    std::string operand;

    if (std::find(commentChars.begin(), commentChars.end(), c) != commentChars.end()) {
      break;
    }

    if (c == '[') {
      std::getline(ss, operand, ']');
      operands.emplace_back(operand + ']');
    } else if (c == '{') {
      std::getline(ss, operand, '}');
      operands.emplace_back(operand + '}');
    } else {
      if (std::isspace(c) || c == ',') {
        ss.ignore();
        continue;
      }

      std::getline(ss, operand, ',');

      if (operand.empty()) {
        continue;
      }

      operand = trimWord(operand);

      if (!operand.empty()) {
        operands.emplace_back(operand);
      }
    }
  }

  const std::string* operandsPtr = operands.data();
  u32 numOperands = static_cast<u32>(operands.size());

  InstructionAST* instrAST;
  if (instr == "nop") {
    instrAST = parseNopInstr(operandsPtr, numOperands);
  } else if (instr == "mov") {
    instrAST = parseMovInstr(operandsPtr, numOperands);
  } else if (instr == "str") {
    instrAST= parseStrInstr(operandsPtr, numOperands);
  } else if (instr == "ldr") {
    instrAST= parseLdrInstr(operandsPtr, numOperands);
  } else if (instr == "push") {
    instrAST= parsePushInstr(operandsPtr, numOperands);
  } else if (instr == "pop") {
    instrAST= parsePopInstr(operandsPtr, numOperands);
  } else if (instr == "add") {
    instrAST= parseAddInstr(operandsPtr, numOperands);
  } else if (instr == "sub") {
    instrAST= parseSubInstr(operandsPtr, numOperands);
  } else if (instr == "b") {
    instrAST= parseBInstr(operandsPtr, numOperands);
  } else if (instr == "beq") {
    instrAST= parseBeqInstr(operandsPtr, numOperands);
  } else if (instr == "bne") {
    instrAST= parseBneInstr(operandsPtr, numOperands);
  } else if (instr == "blt") {
    instrAST= parseBltInstr(operandsPtr, numOperands);
  } else if (instr == "ble") {
    instrAST= parseBleInstr(operandsPtr, numOperands);
  } else if (instr == "bgt") {
    instrAST= parseBgtInstr(operandsPtr, numOperands);
  } else if (instr == "bge") {
    instrAST= parseBgeInstr(operandsPtr, numOperands);
  } else if (instr == "bl") {
    instrAST= parseBlInstr(operandsPtr, numOperands);
  } else if (instr == "bx") {
    instrAST= parseBxInstr(operandsPtr, numOperands);
  } else if (instr == "cmp") {
    instrAST= parseCmpInstr(operandsPtr, numOperands);
  } else {
    std::cout << "Unknown instruction \"" << instr << "\"" << std::endl;
    instrAST = nullptr;
  }

  return instrAST;
}

void Program::verifyProgram() {
  mImpl->mIsValid = mImpl->mLabels.size() < std::numeric_limits<u16>::max() - 1 &&
      std::all_of(
          mImpl->mLabels.cbegin(),
          mImpl->mLabels.cend(),
          [](const LabelAST* const label) {
            return label != nullptr &&
                label->getNumInstructions() < std::numeric_limits<u16>::max() &&
                std::all_of(
                    label->getInstructions(),
                    label->getInstructions() + label->getNumInstructions(),
                    [](const InstructionAST* const instr) {
                      return instr != nullptr;
                    });
          });
}
