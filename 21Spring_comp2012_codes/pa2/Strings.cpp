#include "Strings.h"

#include <sstream>
#include <string>
#include <vector>

namespace {
std::vector<std::string> parseSubExprOperands(const std::string& input) {
  std::stringstream ss{input};
  std::vector<std::string> operands;
  while (!ss.eof()) {
    int c = ss.peek();
    std::string temp;

    if (c == '/' || c == '%' || c == '@') {
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

  return operands;
}
}  // namespace

const char* ERROR_MSG_PREVIOUS = "See previous error";

std::string alignTree(u32 level) {
  std::ostringstream oss;
  for (u32 i = 0; i < level; ++i) {
    if (i == level - 1) {
      oss << "   |-";
    } else {
      oss << "   |";
    }
  }
  return oss.str();
}

std::string makeArgNumErrorString(u32 expected) {
  std::ostringstream oss;
  oss << "Instruction requires ";
  oss << expected;
  oss << " operands";
  return oss.str();
}

std::string* parseSubExprOperands(const std::string& input, u32& numOperands) {
  std::vector<std::string> operands = parseSubExprOperands(input);

  numOperands = static_cast<u32>(operands.size());
  std::string* pOperands = new std::string[numOperands];
  for (std::size_t i = 0; i < numOperands; ++i) {
    pOperands[i] = operands[i];
  }

  return pOperands;
}

std::string trimWord(std::string input) {
  if (input.empty()) {
    return input;
  }

  std::string::size_type firstNonWhitespaceChar = input.find_first_not_of(' ');
  std::string::size_type lastNonWhitespaceChar = input.substr(firstNonWhitespaceChar).find_first_of(' ');

  return input.substr(firstNonWhitespaceChar, lastNonWhitespaceChar);
}

std::string trimLine(std::string input) {
  if (input.empty()) {
    return input;
  }

  std::string::size_type firstChar = input.find_first_not_of(' ');
  std::string::size_type lastChar = input.find_last_not_of(' ');

  return input.substr(firstChar, lastChar + 1);
}
