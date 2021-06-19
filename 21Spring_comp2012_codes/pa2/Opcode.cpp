#include "Opcode.h"

std::string to_string(Op op) {
  switch (op) {
    case Op::NOP:
      return "nop";
    case Op::MOV:
      return "mov";
    case Op::STR:
      return "str";
    case Op::LDR:
      return "ldr";
    case Op::PUSH:
      return "push";
    case Op::POP:
      return "pop";
    case Op::ADD:
      return "add";
    case Op::SUB:
      return "sub";
    case Op::B:
      return "b";
    case Op::BEQ:
      return "beq";
    case Op::BNE:
      return "bne";
    case Op::BLT:
      return "blt";
    case Op::BLE:
      return "ble";
    case Op::BGT:
      return "bgt";
    case Op::BGE:
      return "bge";
    case Op::BL:
      return "bl";
    case Op::BX:
      return "bx";
    case Op::CMP:
      return "cmp";
    default:
      return "unknown";
  }
}
