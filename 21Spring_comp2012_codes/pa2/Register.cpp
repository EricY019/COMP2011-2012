#include "Register.h"

std::string to_string(Register reg) {
  switch (reg) {
    case Register::R0:
      return "r0";
    case Register::R1:
      return "r1";
    case Register::R2:
      return "r2";
    case Register::R3:
      return "r3";
    case Register::R4:
      return "r4";
    case Register::R5:
      return "r5";
    case Register::R6:
      return "r6";
    case Register::R7:
      return "r7";
    case Register::R8:
      return "r8";
    case Register::R9:
      return "r9";
    case Register::R10:
      return "r10";
    case Register::R11:
      return "r11";
    case Register::R12:
      return "r12";
    case Register::R13:
      return "sp/r13";
    case Register::R14:
      return "lr/r14";
    case Register::R15:
      return "pc/r15";
    default:
      return "unknown";
  }
}
