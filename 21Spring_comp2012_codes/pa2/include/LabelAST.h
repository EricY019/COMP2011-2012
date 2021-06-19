#ifndef LABEL_AST_H
#define LABEL_AST_H

#include <string>

#include "AST.h"
#include "Util.h"

class InstructionAST;

/**
 * \brief An AST node which represents a program label.
 *
 * Program labels are locations in the program which certain instructions can jump to. These are analogous to labels in
 * C/C++, used by `goto` statements.
 */
class LabelAST : public AST {
 public:
  /**
   * \param name Name of the label.
   * \param exprs Dynamic array of pointers to `InstructionAST` which are part of this label.
   * \param exprsSize Number of expressions in the `exprs` dynamic array.
   */
  LabelAST(const std::string& name, InstructionAST** exprs, u32 exprsSize);
  ~LabelAST() override;

  const char* getTokenName() const override { return "Label"; }
  void print(u32 indent) const override;

  /**
   * \return The name of this label.
   */
  const std::string& getLabelName() const;
  /**
   * \return The instructions which are part of this label.
   */
  InstructionAST** getInstructions() const;
  /**
   * \return The number of instructions contained in this label.
   */
  u32 getNumInstructions() const;
  /**
   * \brief Retrieves a pointer to an instruction within this label.
   *
   * \param offset The index of the instruction to retrieve.
   * \return Pointer to the instruction, or `nullptr` if the offset is out-of-bounds.
   */
  const InstructionAST* getInstructionByOffset(u32 offset) const;

 private:
  struct Impl;

  Impl* mImpl;
};

#endif  // LABEL_AST_H
