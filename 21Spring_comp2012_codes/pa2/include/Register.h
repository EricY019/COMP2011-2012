#ifndef REGISTER_H
#define REGISTER_H

#include <string>

#include "Util.h"

/**
 * \brief Enumeration of all registers within the processor.
 */
enum struct Register : u8 {
  R0 = 0,
  R1,
  R2,
  R3,
  R4,
  R5,
  R6,
  R7,
  R8,
  R9,
  R10,
  R11,
  R12,
  R13,
  R14,
  R15,

  /**
   * \brief Stack Pointer; Aliases to `r13`.
   */
  SP = R13,
  /**
   * \brief Link Register; Aliases to `r14`.
   */
  LR = R14,
  /**
   * \brief Program Counter; Aliases to `r15`.
   */
  PC = R15
};

/**
 * \return String representation of the specified processor register.
 */
std::string to_string(Register reg);

#endif  // REIGSTER_H
