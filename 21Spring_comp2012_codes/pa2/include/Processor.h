#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>

#include "Util.h"

class MemStack;

class Program;

enum struct Register : u8;

struct StatusRegister;

/**
 * \brief A processor which executes a program.
 */
class Processor {
 public:
  /**
   * \brief Creates a processor instance.
   *
   * @param debug If `true`, outputs the current state of the processor before executing each instruction.
   */
  explicit Processor(bool debug = false);
  ~Processor();

  Processor(const Processor&) = delete;

  Processor& operator=(const Processor&) = delete;

  /**
   * \brief Loads a program into the processor.
   *
   * \param program Program to load. The program instance must be valid until `this` instance is destructed or the
   * program has been unloaded.
   * \return `true` if the program is successfully loaded.
   */
  bool loadProgram(const Program& program);
  /**
   * \brief Unloads a program from the processor.
   */
  void unloadProgram();
  /**
   * \return Pointer to the currently loaded program, or `nullptr` if no program is loaded.
   */
  const Program* getProgram() const;

  /**
   * \brief Sets the entry point of the program.
   *
   * By default, the entrypoint is `main`; This function can be used to change which function will be used as the
   * program entrypoint.
   *
   * \param entrypoint The label name of the desired entrypoint.
   * \return
   */
  bool setEntryPoint(const std::string& entrypoint);
  /**
   * \brief Runs the specified program.
   *
   * This function will run the program until it has exited (or a processor trap has been raised).
   */
  void run();
  /**
   * \brief Steps over one instruction in the program.
   *
   * This function will only execute one instruction in the program.
   */
  void stepInstruction();

  /**
   * \brief Resets the processor.
   *
   * Note that this function does not unload the program, it merely resets all internal state of the processor.
   */
  void reset();

  /**
   * \return `true` if the program has terminated, either normally or via a processor trap.
   */
  bool hasTerminated() const;

  /**
   * The trapped bit is usually set when executing an illegal instruction or the instruction cannot be executed. Setting
   * the trap bit will immediately terminate the program.
   *
   * \return `true` if the processor is "trapped"
   */
  bool hasTrap() const;

  /**
   * \param index Index of the register to retrieve.
   * \return Reference to the specified register.
   */
  u32& getRegister(u8 index);
  /**
   * \param reg Enumeration of the register to retrieve.
   * \return Reference to the specified register.
   */
  u32& getRegister(Register reg);

  /**
   * \param index Index of the register to retrieve.
   * \return Value of the specified register.
   */
  u32 getRegister(u8 index) const;
  /**
   * \param reg Enumeration of the register to retrieve.
   * \return Value of the specified register.
   */
  u32 getRegister(Register reg) const;

  /**
   * \return Reference to the status register.
   */
  StatusRegister& getStatusRegister();
  /**
   * \return Current state of the status register.
   */
  StatusRegister getStatusRegister() const;

  /**
   * \return Reference to the program stack.
   */
  MemStack& getStack();
  /**
   * \return Read-only reference to the program stack.
   */
  const MemStack& getStack() const;

  /**
   * \brief Outputs the current state of the processor.
   */
  void dump() const;

 private:
  struct Impl;

  /**
   * \brief Resolves the name of a label given its label index.
   *
   * \param labelIdx Index of the label.
   * \return Name of the label.
   */
  std::string resolveLabelName(u16 labelIdx) const;

  Impl* mImpl;
};

#endif  // PROCESSOR_H
