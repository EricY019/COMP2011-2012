#ifndef MEM_STACK_H
#define MEM_STACK_H

#include "Util.h"

/**
 * \brief The initial position of the stack pointer on program reset.
 */
extern const u32 STACK_POINTER_BASE;
/**
 * \brief The default size of the program stack.
 */
extern const u32 STACK_SIZE;

/**
 * \brief The memory stack of a program.
 */
class MemStack final {
 public:
  /**
   * \brief Creates a stack with the given size.
   *
   * \param size The maximum size of the stack.
   */
  explicit MemStack(u32 size = STACK_SIZE);
  ~MemStack();

  /**
   * \brief Stores a 32-bit value into a given memory location within the stack.
   *
   * \param value The value to store.
   * \param addr The memory address to store the value to.
   */
  void store(u32 value, u32 addr);

  /**
   * \brief Loads a 32-bit value from a given memory location within the stack.
   *
   * \param addr The base memory address to load the value from.
   * \return The value loaded from the specified address.
   */
  u32 load(u32 addr) const;

  /**
   * \brief Outputs the current state of the stack.
   *
   * \param sp The current memory address of the stack pointer.
   */
  void dump(u32 sp) const;

 private:
  struct Impl;

  Impl* mImpl;
};

#endif  // MEM_STACK_H
