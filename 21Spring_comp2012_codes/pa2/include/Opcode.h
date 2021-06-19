#ifndef OPCODE_H
#define OPCODE_H

#include <string>

/**
 * \brief List of all supported opcodes.
 *
 * See the AST for each of these enumeration values for more information of what they do.
 */
enum struct Op {
  NOP,

  MOV,

  STR,
  LDR,

  PUSH,
  POP,

  ADD,
  SUB,

  B,
  BEQ,
  BNE,
  BLT,
  BLE,
  BGT,
  BGE,
  BL,
  BX,

  CMP,
};

/**
 * \return The string representation of the opcode.
 */
std::string to_string(Op op);

#endif  // OPCODE_H
