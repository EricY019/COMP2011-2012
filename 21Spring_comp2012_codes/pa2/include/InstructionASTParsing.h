#ifndef INSTRUCTION_AST_PARSING_H
#define INSTRUCTION_AST_PARSING_H

#include "BranchInstructionAST.h"
#include "InstructionAST.h"

// All functions below are functions which parse an array of operands into their respective AST nodes. Parsing here
// means to read the operands and convert them into the appropriate AST structure.

NopInstructionAST* parseNopInstr(const std::string* operands, u32 numOperands);
MovInstructionAST* parseMovInstr(const std::string* operands, u32 numOperands);
AddInstructionAST* parseAddInstr(const std::string* operands, u32 numOperands);
SubInstructionAST* parseSubInstr(const std::string* operands, u32 numOperands);
PushInstructionAST* parsePushInstr(const std::string* operands, u32 numOperands);
PopInstructionAST* parsePopInstr(const std::string* operands, u32 numOperands);
StrInstructionAST* parseStrInstr(const std::string* operands, u32 numOperands);
LdrInstructionAST* parseLdrInstr(const std::string* operands, u32 numOperands);
BInstructionAST* parseBInstr(const std::string* operands, u32 numOperands);
BeqInstructionAST* parseBeqInstr(const std::string* operands, u32 numOperands);
BneInstructionAST* parseBneInstr(const std::string* operands, u32 numOperands);
BltInstructionAST* parseBltInstr(const std::string* operands, u32 numOperands);
BleInstructionAST* parseBleInstr(const std::string* operands, u32 numOperands);
BgtInstructionAST* parseBgtInstr(const std::string* operands, u32 numOperands);
BgeInstructionAST* parseBgeInstr(const std::string* operands, u32 numOperands);
BlInstructionAST* parseBlInstr(const std::string* operands, u32 numOperands);
BxInstructionAST* parseBxInstr(const std::string* operands, u32 numOperands);
CmpInstructionAST* parseCmpInstr(const std::string* operands, u32 numOperands);

#endif  // INSTRUCTION_AST_PARSING_H
