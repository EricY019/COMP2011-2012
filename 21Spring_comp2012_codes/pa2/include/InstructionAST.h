#ifndef INSTRUCTION_AST_H
#define INSTRUCTION_AST_H

#include "AST.h"
#include "Opcode.h"
#include "OperandAST.h"

class Processor;

/**
 * \brief An AST node which represents an assembly instruction.
 */
class InstructionAST : public ExprAST {
 public:
  /**
   * \param op The opcode of this instruction.
   */
  explicit InstructionAST(Op op);

  const char* getTokenName() const override = 0;
  /**
   * \brief Evaluates this instruction on the given processor state.
   *
   * \param processor The processor which this instruction should evaluate on.
   */
  virtual void eval(Processor& processor) const = 0;

  /**
   * \return The name of this instruction as it appears in the assembly source code.
   */
  std::string getInstrName() const { return to_string(mOp); }
  /**
   * \return The enumeration of this instruction.
   */
  virtual Op getInstrOp() const { return mOp; };

 private:
  /**
   * \brief Enumeration value representing the operation of this instruction.
   */
  Op mOp;
};

/**
 * \brief An instruction AST which represents the `nop` instruction.
 *
 * The `nop` instruction does nothing.
 */
class NopInstructionAST final : public InstructionAST {
 public:
  NopInstructionAST();
  ~NopInstructionAST() override = default;

  const char* getTokenName() const override { return "NopInstruction"; }
  void print(u32 indent) const override;
  void eval(Processor& processor) const override;
};

/**
 * \brief An instruction AST which represents the `mov` instruction.
 *
 * The `mov` instruction performs copying from either a register or an immediate value into another register.
 *
 * The `mov` instruction is represented with the form of `mov Rd, Operand2`, where `Rd` is the destination register,
 * whereas `Operand2` can be a register or an immediate value.
 *
 * This is equivalent to `Rd = Operand2` in C++.
 */
class MovInstructionAST : public InstructionAST {
 public:
  /**
   * \param dst The first operand of this instruction, i.e. the "destination" register of the `mov` instruction.
   */
  explicit MovInstructionAST(RegisterOperandExprAST* dst);
  ~MovInstructionAST() override;

  const char* getTokenName() const override { return "MovInstruction"; }
  void eval(Processor& processor) const override = 0;
  void print(u32 indent) const override;

 protected:
  /**
   * \return Reference to the destination register.
   */
  const RegisterOperandExprAST& getDst() const;

 private:
  /**
   * \brief The expression representing the destination register of this instruction.
   */
  RegisterOperandExprAST* mDst;
};

/**
 * \brief An instruction AST which represents the register-form of the `mov` instruction.
 *
 * In other words, this specifically represents the `mov Rd, Rn` form of the instruction, where `Rn` is the source
 * register to copy from.
 *
 * This is equivalent to `Rd = Rn` in C++.
 */
class RegMovInstructionAST final : public MovInstructionAST {
 public:
  /**
   * \param dst The first operand of this instruction, i.e. the "destination" register of the `mov` instruction.
   * \param src The second operand of this instruction, i.e. the "source" register of the `mov` instruction.
   */
  explicit RegMovInstructionAST(RegisterOperandExprAST* dst, RegisterOperandExprAST* src);
  ~RegMovInstructionAST() override;

  void eval(Processor& processor) const override;
  void print(u32 indent) const override;

 private:
  /**
   * \brief The expression representing the source register of this instruction.
   */
  RegisterOperandExprAST* mSrc;
};

/**
 * \brief An instruction AST which represents the immediate-form of the `mov` instruction.
 *
 * In other words, this specifically represents the `mov Rd, #imm32` form of the instruction, where `#imm32` is the
 * 32-bit integer value to copy.
 *
 * This is equivalent to `Rd = #imm32` in C++.
 */
class ImmMovInstructionAST final : public MovInstructionAST {
 public:
  /**
   * \param dst The first operand of this instruction, i.e. the "destination" register of the `mov` instruction.
   * \param src The second operand of this instruction, i.e. the "source" value of the `mov` instruction.
   */
  explicit ImmMovInstructionAST(RegisterOperandExprAST* dst, Imm32OperandExprAST* imm);
  ~ImmMovInstructionAST() override;

  void eval(Processor& processor) const override;
  void print(u32 indent) const override;

 private:
  /**
   * \brief The expression representing the source value of this instruction.
   */
  Imm32OperandExprAST* mImm;
};

/**
 * \brief An instruction AST which represents the `add` instruction.
 *
 * The `add` instruction performs addition between two registers or a register and an immediate value, and stores the
 * result into another register.
 *
 * The `add` instruction is represented with the form of `add Rd, Rn, Operand2`, where `Rd` is the destination register,
 * `Rn` is one of the operands, and `Operand2` can be a register or an immediate value.
 *
 * This is equivalent to `Rd = Rn + Operand2`.
 */
class AddInstructionAST : public InstructionAST {
 public:
  /**
   * \param dst The first operand of this instruction, i.e. the "destination" register to store the result of the
   * addition.
   * \param src1 The second operand of this instruction, i.e. the first operand of the addition.
   */
  explicit AddInstructionAST(RegisterOperandExprAST* dst, RegisterOperandExprAST* src1);
  ~AddInstructionAST() override;

  const char* getTokenName() const override { return "AddInstruction"; }
  void print(u32 indent) const override;
  void eval(Processor& processor) const override = 0;

 protected:
  /**
   * \return Reference to the destination register.
   */
  const RegisterOperandExprAST& getDst() const;
  /**
   * \return Reference to the first operand of the addition.
   */
  const RegisterOperandExprAST& getSrc1() const;

 private:
  /**
   * \brief The expression representing the target register to store the result to.
   */
  RegisterOperandExprAST* mDst;
  /**
   * \brief The expression representing the source register of the first operand of the addition.
   */
  RegisterOperandExprAST* mSrc1;
};

/**
 * \brief An instruction AST which represents the register-form of the `add` instruction.
 *
 * In other words, this specifically represents the `add Rd, Rn, Rm` form of the instruction, where `Rm` is the second
 * operand of the addition.
 *
 * This is equivalent to `Rd = Rn + Rm` in C++.
 */
class RegAddInstructionAST final : public AddInstructionAST {
 public:
  /**
   * \param dst The first operand of this instruction, i.e. the "destination" register to store the result of the
   * addition.
   * \param src2 The third operand of this instruction, i.e. the second register operand of the addition.
   */
  RegAddInstructionAST(RegisterOperandExprAST* dst, RegisterOperandExprAST* src1, RegisterOperandExprAST* src2);
  ~RegAddInstructionAST() override;

  void print(u32 indent) const override;
  void eval(Processor& processor) const override;

 private:
  /**
   * \brief The expression representing the source register of the second operand of the addition.
   */
  RegisterOperandExprAST* mSrc2;
};

/**
 * \brief An instruction AST which represents the immediate-form of the `add` instruction.
 *
 * In other words, this specifically represents the `add Rd, Rn, #imm32` form of the instruction, where `#imm32` is the
 * 32-bit integer operand of the addition.
 *
 * This is equivalent to `Rd = Rn + #imm32` in C++.
 */
class ImmAddInstructionAST final : public AddInstructionAST {
 public:
  /**
   * \param dst The first operand of this instruction, i.e. the "destination" register to store the result of the
   * addition.
   * \param src The second operand of this instruction, i.e. the first register operand of the addition.
   * \param imm The third operand of this instruction, i.e. the second immediate operand of the addition.
   */
  ImmAddInstructionAST(RegisterOperandExprAST* dst, RegisterOperandExprAST* src, Imm32OperandExprAST* imm);
  ~ImmAddInstructionAST() override;

  void print(u32 indent) const override;
  void eval(Processor& processor) const override;

 private:
  /**
   * \brief The expression representing the constant value of the second operand of the addition.
   */
  Imm32OperandExprAST* mImm;
};

/**
 * \brief An instruction AST which represents the `sub` instruction.
 *
 * The `sub` instruction performs subtraction between two registers or a register and an immediate value, and stores the
 * result into another register.
 *
 * The `sub` instruction is represented with the form of `sub Rd, Rn, Operand2`, where `Rd` is the destination register,
 * `Rn` is one of the operands, and `Operand2` can be a register or an immediate value.
 *
 * This is equivalent to `Rd = Rn - Operand2`.
 */
class SubInstructionAST : public InstructionAST {
 public:
  /**
   * \param dst The first operand of this instruction, i.e. the "destination" register of the `sub` instruction.
   * \param src1 The second operand of this instruction, i.e. the register operand to subtract from.
   */
  explicit SubInstructionAST(RegisterOperandExprAST* dst, RegisterOperandExprAST* src1);
  ~SubInstructionAST() override;

  const char* getTokenName() const override { return "SubInstruction"; }
  void print(u32 indent) const override;
  void eval(Processor& processor) const override = 0;

 protected:
  /**
   * \return Reference to the destination register.
   */
  const RegisterOperandExprAST& getDst() const;
  /**
   * \return Reference to the first operand of the subtraction.
   */
  const RegisterOperandExprAST& getSrc1() const;

 private:
  /**
   * \brief The expression representing the target register to store the result to.
   */
  RegisterOperandExprAST* mDst;
  /**
   * \brief The expression representing the source register of the first operand of the subtraction.
   */
  RegisterOperandExprAST* mSrc1;
};

/**
 * \brief An instruction AST which represents the register-form of the `sub` instruction.
 *
 * In other words, this specifically represents the `sub Rd, Rn, Rm` form of the instruction, where `Rm` is the second
 * operand of the subtraction.
 *
 * This is equivalent to `Rd = Rn - Rm` in C++.
 */
class RegSubInstructionAST final : public SubInstructionAST {
 public:
  /**
   * \param dst The first operand of this instruction, i.e. the "destination" register to store the result of the
   * subtraction.
   * \param src1 The second operand of this instruction, i.e. the first register operand of the subtraction.
   * \param src2 The third operand of this instruction, i.e. the second register operand of the subtraction.
   */
  RegSubInstructionAST(RegisterOperandExprAST* dst, RegisterOperandExprAST* src1, RegisterOperandExprAST* src2);
  ~RegSubInstructionAST() override;

  void print(u32 indent) const override;
  void eval(Processor& processor) const override;

 private:
  /**
   * \brief The expression representing the source register of the second operand of the addition.
   */
  RegisterOperandExprAST* mSrc2;
};

/**
 * \brief An instruction AST which represents the immediate-form of the `sub` instruction.
 *
 * In other words, this specifically represents the `sub Rd, Rn, #imm32` form of the instruction, where `#imm32` is the
 * 32-bit integer operand of the subtraction.
 *
 * This is equivalent to `Rd = Rn - #imm32` in C++.
 */
class ImmSubInstructionAST final : public SubInstructionAST {
 public:
  /**
   * \param dst The first operand of this instruction, i.e. the "destination" register to store the result of the
   * subtraction.
   * \param src The second operand of this instruction, i.e. the first register operand of the subtraction.
   * \param imm The third operand of this instruction, i.e. the second immediate operand of the subtraction.
   */
  ImmSubInstructionAST(RegisterOperandExprAST* dst, RegisterOperandExprAST* src, Imm32OperandExprAST* imm);
  ~ImmSubInstructionAST() override;

  void print(u32 indent) const override;
  void eval(Processor& processor) const override;

 private:
  /**
   * \brief The expression representing the constant value of the second operand of the addition.
   */
  Imm32OperandExprAST* mImm;
};

/**
 * \brief An instruction AST which represents the `push` instruction.
 *
 * The `push` instruction stores the values of all registers in the register-list into the stack memory, by first
 * decrementing the stack pointer, then storing the value of each register into the stack.
 *
 * The `push` instruction is represented with the form of `push reglist`, where `reglist` is a list of comma-separated
 * registers enclosed in curly braces (e.g. `{r0, r1}`).
 *
 * Note that this instruction stores lower number registers in lower address. For example, if the stack pointer is
 * currently at 0x88, `r0` will be stored in `0x80` (occupying 0x80 to 0x83), and `r1` will be stored in `0x84`
 * (occupying 0x84 to 0x87). The stack pointer after executing the instruction will be at 0x80.
 */
class PushInstructionAST final : public InstructionAST {
 public:
  /**
   * \param regList The first operand of this instruction, i.e. the list of registers whose values need to be stored on
   * the stack.
   */
  explicit PushInstructionAST(RegisterListOperandExprAST* regList);
  ~PushInstructionAST() override;

  const char* getTokenName() const override { return "PushInstruction"; }
  void eval(Processor& processor) const override;
  void print(u32 indent) const override;

 private:
  /**
   * \brief The expression representing the list of registers which needs to be stored in the stack.
   */
  RegisterListOperandExprAST* mRegList;
};

/**
 * \brief An instruction AST which represents the `pop` instruction.
 *
 * The `pop` instruction loads the values of all registers in the register-list from the stack memory, by first
 * loading the value of each register from the stack, then incrementing the stack pointer.
 *
 * The `pop` instruction is represented with the form of `pop reglist`, where `reglist` is a list of comma-separated
 * registers enclosed in curly braces (e.g. `{r0, r1}`).
 *
 * Note that this instruction loads lower number registers in lower address. For example, if the stack pointer is
 * currently at 0x80, `r0` will be loaded from `0x80`, and `r1` will be loaded from `0x84`. The stack pointer after
 * executing the instruction will be at 0x88.
 */
class PopInstructionAST final : public InstructionAST {
 public:
  /**
   * \param regList The first operand of this instruction, i.e. the list of registers whose values need to be loaded
   * from the stack.
   */
  explicit PopInstructionAST(RegisterListOperandExprAST* regList);
  ~PopInstructionAST() override;

  const char* getTokenName() const override { return "PopInstruction"; }
  void eval(Processor& processor) const override;
  void print(u32 indent) const override;

 private:
  /**
   * \brief The expression representing the list of registers which needs to be loaded from the stack.
   */
  RegisterListOperandExprAST* mRegList;
};

/**
 * \brief An instruction AST which represents the `str` instruction.
 *
 * The `str` instruction stores the value of a register into the stack memory.
 *
 * The `str` instruction is represented with the form of `str Rt, [Rn {, #offset}]`, where `Rt` is the target register
 * (whose value need to be stored), `Rn` is the address to store into, and `#offset` is the optional offset from `Rn` in
 * bytes.
 *
 * This is equivalent to `*(u32*)((char*) Rn + offset) = Rt` in C++.
 */
class StrInstructionAST final : public InstructionAST {
 public:
  /**
   * \param src The first operand of this instruction, i.e. the source register to store into the stack.
   * \param dst The second operand of this instruction, i.e. the memory location which the value should be stored into.
   */
  StrInstructionAST(RegisterOperandExprAST* src, IndirectOperandExprAST* dst);
  ~StrInstructionAST() override;

  const char* getTokenName() const override { return "StrInstruction"; }
  void print(u32 indent) const override;
  void eval(Processor& processor) const override;

 private:
  /**
   * \brief The expression representing the register whose value needs to be stored to the stack.
   */
  RegisterOperandExprAST* mSrc;
  /**
   * \brief The expression representing the stack memory location (and offset) to store the register value into.
   */
  IndirectOperandExprAST* mDst;
};

/**
 * \brief An instruction AST which represents the `ldr` instruction.
 *
 * The `ldr` instruction loads the value of a register from stack memory.
 *
 * The `ldr` instruction is represented with the form of `ldr Rt, [Rn {, #offset}]`, where `Rt` is the target register
 * (where the value will be loaded into), `Rn` is the address to load from, and `#offset` is the optional offset from
 * `Rn` in bytes.
 *
 * This is equivalent to `Rt = *(u32*)((char*) Rn + offset)` in C++.
 */
class LdrInstructionAST final : public InstructionAST {
 public:
  /**
   * \param dst The first operand of this instruction, i.e. the "target" register to load into from the stack.
   * \param src The second operand of this instruction, i.e. the memory location which the value should be loaded from.
   */
  LdrInstructionAST(RegisterOperandExprAST* dst, IndirectOperandExprAST* src);
  ~LdrInstructionAST() override;

  const char* getTokenName() const override { return "LdrInstruction"; }
  void print(u32 indent) const override;
  void eval(Processor& processor) const override;

 private:
  /**
   * \brief The expression representing the register whose value needs to be loaded from the stack.
   */
  RegisterOperandExprAST* mDst;
  /**
   * \brief The expression representing the stack memory location (and offset) to load the register value from.
   */
  IndirectOperandExprAST* mSrc;
};

void printParseError(const char* instrName, const char* explanation);
void printParseError(const char* instrName, const std::string& explanation);

#endif  // INSTRUCTION_AST_H
