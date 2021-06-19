#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>

#include "Util.h"

class LabelAST;

class InstructionAST;

/**
 * \brief An assembly program that may be executed by the Processor.
 */
class Program final {
 public:
  /**
   * \brief Creates a program using the provided assembly code.
   *
   * \param program Input assembly code.
   */
  explicit Program(const std::string& program);
  ~Program();

  /**
   * \brief Returns the index of a label using its name.
   *
   * \param name The name of the label.
   * \return The index of the label, or `-1` if the label does not exist within this program.
   */
  long getLabelIndexByName(const std::string& name) const;
  /**
   * \brief Returns the index of a label using its pointer.
   *
   * \param label Pointer to the label.
   * \return The index of the label, or `-1` if the label does not exist within this program.
   */
  long getLabelIndexByLabel(const LabelAST* label) const;
  /**
   * \brief Returns a pointer to a label using its index.
   *
   * \param index The index of the label.
   * \return Pointer to the label, or `nullptr` if the label does not exist within this program.
   */
  const LabelAST* getLabelByIndex(u32 index) const;
  /**
   * \brief Returns a pointer to a label using its name.
   *
   * \param name The name of the label.
   * \return Pointer to the label, or `nullptr`, if the label does not exist within this program.
   */
  const LabelAST* getLabelByName(const std::string& name) const;

  /**
   * \return Whether the program is valid, i.e. there were no errors when parsing the source code of this program.
   */
  bool isValid() const;

  /**
   * \brief Prints the AST of this program, including all labels, their instructions and operands.
   */
  void printAST() const;

 private:
  struct Impl;

  /**
   * \brief Converts the given input program into an AST representing a label starting from the given position.
   *
   * \param input The input program source.
   * \param pos The position to start parsing from.
   * \return A `LabelAST*` representing the parsed AST, or `nullptr` if parsing was unsuccessful.
   */
  LabelAST* parseLabel(const std::string& input, u32& pos);
  /**
   * \brief Converts the given input into an AST representing an instruction.
   *
   * \param input The instruction to parse.
   * \return An `InstructionAST*` representing the parsed AST, or `nullptr` if parsing was unsuccessful.
   */
  InstructionAST* parseInstruction(const std::string& input);

  /**
   * \brief Verifies whether the program is valid, i.e. no error have occurred while parsing the source code.
   */
  void verifyProgram();

  Impl* mImpl;
};

#endif  // PROGRAM_H
