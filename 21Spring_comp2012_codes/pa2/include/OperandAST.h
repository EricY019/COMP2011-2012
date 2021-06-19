#ifndef OPERAND_AST_H
#define OPERAND_AST_H

#include "AST.h"
#include "Register.h"
#include "Util.h"

class InstructionAST;

class LabelAST;

/**
 * \brief An expression which represents an instruction operand.
 */
class OperandExprAST : public ExprAST {
 public:
  /**
   * \return The name of this operand.
   */
  const char* getTokenName() const override = 0;
};

/**
 * \brief An expression which represents a register operand.
 *
 * Register operands represents registers within a processor, and are usually written as `r0`~`r15` in ARM assembly.
 * Special registers have aliases, e.g. `sp` is `r13`, `lr` is `r14`, and `pc` is `r15`.
 */
class RegisterOperandExprAST final : public OperandExprAST {
 public:
  /**
   * \param rx The index of the register represented by this expression.
   */
  explicit RegisterOperandExprAST(u8 rx);
  ~RegisterOperandExprAST() override;

  void print(u32 indent) const override;

  const char* getTokenName() const override { return "RegisterOperand"; }

  /**
   * \return The register represented by this expression.
   */
  Register getRegister() const;

  /**
   * \return The index of the register represented by this expression.
   */
  u8 getRegisterIndex() const;

 private:
  u8 mRegister;
};

/**
 * \brief An expression which represents a register-list operand.
 *
 * Register-list operand represent a list of registers, and are usually written as a comma-separated list of registers
 * enclosed in curly braces (`{r0, r1, ...}`) in ARM assembly.
 */
class RegisterListOperandExprAST final : public OperandExprAST {
 public:
  /**
   * \param reglist The register bitmask represented by this expression.
   */
  explicit RegisterListOperandExprAST(u16 reglist);
  void print(u32 indent) const override;

  const char* getTokenName() const override { return "RegListOperand"; }

  /**
   * Check whether a register is present in this list.
   *
   * \param rx The register index to check.
   * \return Whether the specified register is in this register list.
   */
  bool hasRegister(u8 rx) const;

  /**
   * Check whether a register is present in this list.
   *
   * \param reg The register to check.
   * \return Whether the specified register is in this register list.
   */
  bool hasRegister(Register reg) const;

  /**
   * \return The number of registers in this register list.
   */
  u8 getListCount() const;

 private:
  u16 mRegList;
};

/**
 * \brief An expression which represents an immediate operand.
 *
 * Immediate operands represent a constant value within the program; in other words, these values are not dependent on
 * the runtime state of the processor. They are like compile-time constants in C++.
 *
 * These are usually written as a number prepended by a pound-sign (`#`) in ARM assembly.
 */
class ImmOperandExprAST : public OperandExprAST {
 public:
  const char* getTokenName() const override = 0;

  /**
   * \return The value of this operand as a signed 16-bit integer.
   */
  s16 getSigned16() const;
  /**
   * \return The value of this operand as an unsigned 16-bit integer.
   */
  virtual u16 getUnsigned16() const = 0;
  /**
   * \return The value of this operand as a signed 32-bit integer.
   */
  s32 getSigned32() const;
  /**
   * \return The value of this operand as an unsigned 32-bit integer.
   */
  virtual u32 getUnsigned32() const = 0;
};

/**
 * \brief An expression which represents a 16-bit immediate operand.
 */
class Imm16OperandExprAST final : public ImmOperandExprAST {
 public:
  explicit Imm16OperandExprAST(s16 value);
  void print(u32 indent) const override;

  const char* getTokenName() const override { return "Imm16Operand"; }

  u16 getUnsigned16() const override;
  u32 getUnsigned32() const override;

 private:
  u16 mValue;
};

/**
 * \brief An expression which represents a 32-bit immediate operand.
 */
class Imm32OperandExprAST final : public ImmOperandExprAST {
 public:
  explicit Imm32OperandExprAST(s32 value);
  void print(u32 indent) const override;

  const char* getTokenName() const override { return "Imm32Operand"; }

  u16 getUnsigned16() const override;
  u32 getUnsigned32() const override;

 private:
  u32 mValue;
};

/**
 * \brief An expression which represents an indirect operand.
 *
 * Indirect operands represent a value obtained by dereferencing a memory location with an optional offset.
 *
 * These are usually written as a register enclosed within square brackets (`[r0]`), or a register and an immediate
 * operand enclosed within square brackets (`[r0, #4]`).
 *
 * For example:
 * - `[r0]` is equivalent to `*((char*) r0)`
 * - `[r0, #4]` is equivalent to `*((char*) r0 + 4)`
 */
class IndirectOperandExprAST : public OperandExprAST {
 public:
  explicit IndirectOperandExprAST(RegisterOperandExprAST* target, ImmOperandExprAST* offset = nullptr);
  ~IndirectOperandExprAST() override;
  void print(u32 indent) const override;

  const char* getTokenName() const override { return "IndirectOperand"; }

  /**
   * \return The target register storing the memory location to dereference from.
   */
  RegisterOperandExprAST& getRegisterTarget() const;
  /**
   * \return The offset to the target memory location to dereference.
   */
  s16 getOffset() const;

 private:
  RegisterOperandExprAST* mTarget;
  ImmOperandExprAST* mOffset;
};

/**
 * \brief An expression which represents a label.
 *
 * Label operands represent a named label within the program.
 */
class LabelOperandExprAST final : public OperandExprAST {
 public:
  explicit LabelOperandExprAST(const std::string& name);
  void print(u32 indent) const override;

  const char* getTokenName() const override { return "LabelOperand"; }

  /**
   * \return The name of the label.
   */
  const std::string& getLabelName() const;

 private:
  std::string mName;
};

RegisterOperandExprAST* parseRegisterOp(const std::string& operand);
RegisterListOperandExprAST* parseRegisterListOp(const std::string& operand);
Imm16OperandExprAST* parseImm16Op(const std::string& operand);
Imm32OperandExprAST* parseImm32Op(const std::string& operand);
IndirectOperandExprAST* parseIndirectOp(const std::string& operand);
LabelOperandExprAST* parseLabelOp(const std::string& operand);

#endif  // OPERAND_AST_H
