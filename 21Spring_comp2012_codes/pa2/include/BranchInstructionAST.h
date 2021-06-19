#ifndef BRANCH_INSTRUCTION_AST_H
#define BRANCH_INSTRUCTION_AST_H

#include "InstructionAST.h"

/**
 * \brief An instruction AST which represents the `b` instruction.
 *
 * The `b` instruction causes the program execution to immediately jump to a label.
 *
 * The `b` instruction is represented with the form of `b label`, where `label` is the target label to jump to.
 *
 * This is equivalent to `goto label` in C++.
 */
class BInstructionAST : public InstructionAST {
 public:
  /**
   * \param targetLabel The operand of this instruction, i.e. the target label name to jump to.
   */
  explicit BInstructionAST(LabelOperandExprAST* targetLabel);
  ~BInstructionAST() override;

  const char* getTokenName() const override { return "BInstruction"; }
  void print(u32 indent) const override;
  void eval(Processor& processor) const override;

 private:
  LabelOperandExprAST* mTargetLabel;
};

/**
 * \brief An abstract instruction AST which represents a conditional `b` instruction.
 *
 * This class is used to abstract some implementation detail for implementing conditional branching instructions. These
 * instructions are usually used when writing the equivalent of `if`, `while`, and `for` control flow structures in C++.
 */
class BConditionalInstructionAST : public BInstructionAST {
 public:
  /**
   * \param targetLabel The operand of this instruction, i.e. the target label name to jump to if the condition is
   * satisfied.
   */
  explicit BConditionalInstructionAST(LabelOperandExprAST* targetLabel);

  const char* getTokenName() const override = 0;
  void eval(Processor& processor) const final;

 protected:
  /**
   * \brief Checks whether the condition represented by this instruction is satisfied.
   *
   * \param processor The processor state.
   * \return `true` if the condition is satisfied.
   */
  virtual bool checkCondition(const Processor& processor) const = 0;
};

/**
 * \brief An instruction AST which represents the `b` instruction which executes if a previous conditional instruction
 * determines that two operands are equal.
 *
 * This is equivalent to `if (op1 == op2) goto label`.
 */
class BeqInstructionAST final : public BConditionalInstructionAST {
 public:
  explicit BeqInstructionAST(LabelOperandExprAST* targetLabel);

  const char* getTokenName() const override { return "BeqInstruction"; }
  bool checkCondition(const Processor& processor) const override;

  Op getInstrOp() const final { return Op::BEQ; }
};

/**
 * \brief An instruction AST which represents the `b` instruction which executes if a previous conditional instruction
 * determines that two operands are not equal.
 *
 * This is equivalent to `if (op1 != op2) goto label`.
 */
class BneInstructionAST final : public BConditionalInstructionAST {
 public:
  explicit BneInstructionAST(LabelOperandExprAST* targetLabel);

  const char* getTokenName() const override { return "BneInstruction"; }
  bool checkCondition(const Processor& processor) const override;

  Op getInstrOp() const final { return Op::BNE; }
};

/**
 * \brief An instruction AST which represents the `b` instruction which executes if a previous conditional instruction
 * determines that the first operand is less than the second operand.
 *
 * This is equivalent to `if (op1 < op2) goto label`.
 */
class BltInstructionAST final : public BConditionalInstructionAST {
 public:
  explicit BltInstructionAST(LabelOperandExprAST* targetLabel);

  const char* getTokenName() const override { return "BltInstruction"; }
  bool checkCondition(const Processor& processor) const override;

  Op getInstrOp() const final { return Op::BLT; }
};

/**
 * \brief An instruction AST which represents the `b` instruction which executes if a previous conditional instruction
 * determines that the first operand is less or equal to the second operand.
 *
 * This is equivalent to `if (op1 <= op2) goto label`.
 */
class BleInstructionAST final : public BConditionalInstructionAST {
 public:
  explicit BleInstructionAST(LabelOperandExprAST* targetLabel);

  const char* getTokenName() const override { return "BleInstruction"; }
  bool checkCondition(const Processor& processor) const override;

  Op getInstrOp() const final { return Op::BLE; }
};

/**
 * \brief An instruction AST which represents the `b` instruction which executes if a previous conditional instruction
 * determines that the first operand is greater than the second operand.
 *
 * This is equivalent to `if (op1 > op2) goto label`.
 */
class BgtInstructionAST final : public BConditionalInstructionAST {
 public:
  explicit BgtInstructionAST(LabelOperandExprAST* targetLabel);

  const char* getTokenName() const override { return "BgtInstruction"; }
  bool checkCondition(const Processor& processor) const override;

  Op getInstrOp() const final { return Op::BGT; }
};

/**
 * \brief An instruction AST which represents the `b` instruction which executes if a previous conditional instruction
 * determines two operands are equal.
 *
 * This is equivalent to `if (op1 >= op2) goto label`.
 */
class BgeInstructionAST final : public BConditionalInstructionAST {
 public:
  explicit BgeInstructionAST(LabelOperandExprAST* targetLabel);

  const char* getTokenName() const override { return "BgeInstruction"; }
  bool checkCondition(const Processor& processor) const override;

  Op getInstrOp() const final { return Op::BGE; }
};

/**
 * \brief An instruction AST which represents the `bl` instruction.
 *
 * The `bl` instruction stores the address of the next instruction into the Link Register (`lr`), then immediately jumps
 * to a label.
 *
 * The `bl` instruction is represented with the form of `bl label`, where `label` is the target label to jump to.
 *
 * This instruction is usually used when writing the equivalent of "calling functions" in C++, where it is anticipated
 * that the control flow of the program will eventually return to this instruction.
 */
class BlInstructionAST final : public InstructionAST {
 public:
  explicit BlInstructionAST(LabelOperandExprAST* targetLabel);
  ~BlInstructionAST() override;

  const char* getTokenName() const override { return "BlInstruction"; }
  void print(u32 indent) const override;
  void eval(Processor& processor) const override;

 private:
  LabelOperandExprAST* mTargetLabel;
};

/**
 * \brief An instruction AST which represents the `bx` instruction.
 *
 * The `bx` instruction sets the Program Counter (`pc`) from the operand.
 *
 * The `bx` instruction` is represented with the form of `bx Rm`, where `Rm` is the register storing the address of the
 * next instruction the processor should execute.
 *
 * This instruction is usually used when writing the equivalent of "returning from functions" in C++, where the control
 * flow of the program needs to be restored based on a previous register (usually `lr`).
 */
class BxInstructionAST final : public InstructionAST {
 public:
  explicit BxInstructionAST(RegisterOperandExprAST* retAddrReg);
  ~BxInstructionAST() override;

  const char* getTokenName() const override { return "BxInstruction"; }
  void print(u32 indent) const override;
  void eval(Processor& processor) const override;

 private:
  RegisterOperandExprAST* mRetAddrReg;
};

/**
 * \brief An instruction AST which represents the `cmp` instruction.
 *
 * The `cmp` instruction compares two register or one register and one immediate value, and sets the appropriate status
 * register bits in the processor.
 *
 * The `cmp` instruction is represented with the form of `cmp Rn, Operand2`, where `Rn` is the first register operand,
 * and `Operand2` can be a register or an immediate value.
 */
class CmpInstructionAST : public InstructionAST {
 public:
  explicit CmpInstructionAST(RegisterOperandExprAST* operand1);
  ~CmpInstructionAST() override;

  const char* getTokenName() const override { return "CmpInstruction"; }
  void print(u32 indent) const override;
  void eval(Processor& processor) const override = 0;
  void eval(Processor& processor, u32 op2Value) const;

 protected:
  const RegisterOperandExprAST& getOperand1() const;

 private:
  RegisterOperandExprAST* mRegOperand1;
};

/**
 * \brief An instruction AST which represents the register-form of the `cmp` instruction.
 *
 * In other words, this specifically represents the `cmp Rn, Rm`, where `Rm` is the second register operand to compare
 * against.
 */
class RegCmpInstructionAST final : public CmpInstructionAST {
 public:
  explicit RegCmpInstructionAST(RegisterOperandExprAST* operand1, RegisterOperandExprAST* operand2);
  ~RegCmpInstructionAST() override;

  void print(u32 indent) const override;
  void eval(Processor& processor) const override;

 private:
  RegisterOperandExprAST* mRegOperand2;
};

/**
 * \brief An instruction AST which represents the register-form of the `cmp` instruction.
 *
 * In other words, this specifically represents the `cmp Rn, #imm32`, where `#imm32` is the second immediate operand to
 * compare against.
 */
class ImmCmpInstructionAST final : public CmpInstructionAST {
 public:
  explicit ImmCmpInstructionAST(RegisterOperandExprAST* operand1, Imm32OperandExprAST* operand2);
  ~ImmCmpInstructionAST() override;

  void print(u32 indent) const override;
  void eval(Processor& processor) const override;

 private:
  Imm32OperandExprAST* mImmOperand2;
};

#endif  // BRANCH_INSTRUCTION_AST_H
