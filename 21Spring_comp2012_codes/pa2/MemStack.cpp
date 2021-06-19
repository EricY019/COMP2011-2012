#include "MemStack.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

const u32 STACK_POINTER_BASE = 1u << 31;
const u32 STACK_SIZE = (1 << 14);  // 16K stack size

struct MemStack::Impl {
  std::vector<u8> mStack;
};

MemStack::MemStack(u32 size) :
    mImpl{new Impl{std::vector<u8>(size)}} {}

MemStack::~MemStack() {
  delete mImpl;
}

void MemStack::store(u32 value, u32 addr) {
  s32 idx = STACK_POINTER_BASE - (addr + 4);

  if (idx < 0) {
    std::cerr << "Error: MemStack::store: Writing to an address which is not part of the stack.\n"
              << "\tRequested Address: "
              << "0x" << std::hex << std::setfill('0') << std::setw(8) << addr
              << std::dec << std::setfill(' ') << '\n';

    std::abort();
  }
  if ((idx + 4) > static_cast<s32>(mImpl->mStack.size())) {
    std::cerr << "Error: MemStack::store: Writing to an address which exceeds the stack size.\n"
              << "\tStack Size: " << STACK_SIZE << '\n'
              << "\tStack Address Range: "
              << "0x" << std::hex << std::setfill('0') << std::setw(8) << STACK_POINTER_BASE
              << "~0x" << std::hex << std::setfill('0') << std::setw(8) << (STACK_POINTER_BASE - STACK_SIZE)
              << std::dec << std::setfill(' ') << '\n'
              << "\tRequested Address: "
              << "0x" << std::hex << std::setfill('0') << std::setw(8) << addr
              << "~0x" << std::hex << std::setfill('0') << std::setw(8) << (addr + 3)
              << std::dec << std::setfill(' ') << '\n'
              << "\tThis may indicate a stack overflow.\n";

    std::abort();
  }
  if (idx % 4 != 0) {
    std::cerr << "Error: MemStack::store: Writing to an address which is not 4-byte aligned.\n"
              << "\tRequested Address: "
              << "0x" << std::hex << std::setfill('0') << std::setw(8) << addr
              << std::dec << std::setfill(' ') << '\n';

    std::abort();
  }

  u32 stackOffset = static_cast<u32>(idx);
  std::copy_n(reinterpret_cast<char*>(&value), sizeof(u32), &mImpl->mStack[stackOffset]);
}

u32 MemStack::load(u32 addr) const {
  s32 idx = STACK_POINTER_BASE - (addr + 4);

  if (idx < 0) {
    std::cerr << "Error: MemStack::load: Reading from an address which is not part of the stack.\n"
              << "\tRequested Address: "
              << "0x" << std::hex << std::setfill('0') << std::setw(8) << addr
              << std::dec << std::setfill(' ') << '\n';

    std::abort();
  }
  if ((idx + 4) > static_cast<s32>(mImpl->mStack.size())) {
    std::cerr << "Error: MemStack::load: Reading from an address which exceeds the stack size.\n"
              << "\tStack Size: " << STACK_SIZE << '\n'
              << "\tStack Address Range: "
              << "0x" << std::hex << std::setfill('0') << std::setw(8) << STACK_POINTER_BASE
              << "~0x" << std::hex << std::setfill('0') << std::setw(8) << (STACK_POINTER_BASE - STACK_SIZE)
              << std::dec << std::setfill(' ') << '\n'
              << "\tRequested Address: "
              << "0x" << std::hex << std::setfill('0') << std::setw(8) << addr
              << "~0x" << std::hex << std::setfill('0') << std::setw(8) << (addr + 3)
              << std::dec << std::setfill(' ') << '\n'
              << "\tThis may indicate a stack overflow.\n";

    std::abort();
  }
  if (idx % 4 != 0) {
    std::cerr << "Error: MemStack::load: Reading from an address which is not 4-byte aligned.\n"
              << "\tRequested Address: "
              << "0x" << std::hex << std::setfill('0') << std::setw(8) << addr
              << std::dec << std::setfill(' ') << '\n';

    std::abort();
  }

  u32 stackOffset = static_cast<u32>(idx);
  u32 value = 0;
  std::copy_n(&mImpl->mStack[stackOffset], sizeof(u32), reinterpret_cast<char*>(&value));
  return value;
}

void MemStack::dump(u32 sp) const {
  const u32 limit = (STACK_POINTER_BASE - sp) / 4;

  if (limit > 0) {
    std::cout << "Stack Memory Contents:\n";
    for (u32 i = 0; i < limit; ++i) {
      std::cout << "[" << i << ":0x"
                << std::hex << std::setfill('0') << std::setw(8)
                << (STACK_POINTER_BASE - (i * 4) - 1)
                << "~0x"
                << std::hex << std::setfill('0') << std::setw(8)
                << (STACK_POINTER_BASE - ((i + 1) * 4))
                << "] 0x"
                << std::hex << std::setfill('0') << std::setw(8)
                << reinterpret_cast<const u32*>(mImpl->mStack.data())[i]
                << std::dec << std::setfill(' ') << '\n';
    }
    std::cout << std::endl;
  }
}
