#include "Processor.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>

#include "InstructionAST.h"
#include "LabelAST.h"
#include "MemStack.h"
#include "Program.h"
#include "Register.h"
#include "StatusRegister.h"

struct Processor::Impl {
  ~Impl();

  const Program* mProgram;
  const InstructionAST* mCurrentInstr;
  u32 mRegisters[16];
  StatusRegister mStatusReg;
  MemStack* mStack;

  bool mDebug;
};

Processor::Impl::~Impl() {
  delete mStack;
}

Processor::Processor(bool debug) :
    mImpl{new Impl{nullptr, nullptr, {}, {}, new MemStack{}, debug}} {}

Processor::~Processor() {
  delete mImpl;
}

const Program* Processor::getProgram() const { return mImpl->mProgram; }

bool Processor::loadProgram(const Program& program) {
  if (!program.isValid()) {
    return false;
  }

  reset();
  mImpl->mProgram = &program;
  setEntryPoint("main");

  return true;
}

void Processor::unloadProgram() {
  mImpl->mProgram = nullptr;
}

bool Processor::setEntryPoint(const std::string& entrypoint) {
  if (!mImpl->mProgram) {
    return false;
  }

  long entryLabelIdx = mImpl->mProgram->getLabelIndexByName(entrypoint);
  if (entryLabelIdx < 0) {
    return false;
  }

  getRegister(Register::LR) = std::numeric_limits<u32>::max();
  getRegister(Register::PC) = static_cast<u32>(entryLabelIdx & ((1 << 16) - 1)) << 16;

  return true;
}

void Processor::run() {
  if (!mImpl->mProgram) {
    return;
  }

  while (!hasTerminated()) {
    stepInstruction();
  }
}

void Processor::stepInstruction() {
  if (!mImpl->mProgram) {
    return;
  }

  if (hasTerminated()) {
    return;
  }

  u32& pc = getRegister(Register::PC);

  const LabelAST* instrLabel = mImpl->mProgram->getLabelByIndex(pc >> 16);
  if (!instrLabel) {
    mImpl->mStatusReg.mT = true;
    return;
  }

  mImpl->mCurrentInstr = instrLabel->getInstructionByOffset(pc & ((1 << 16) - 1));
  pc += 1;

  if (!mImpl->mCurrentInstr) {
    getStatusRegister().mT = true;
    return;
  }

  if (mImpl->mDebug) {
    dump();
  }
  mImpl->mCurrentInstr->eval(*this);
}

void Processor::reset() {
  mImpl->mCurrentInstr = nullptr;
  std::fill(std::begin(mImpl->mRegisters), std::end(mImpl->mRegisters), 0u);
  getRegister(Register::SP) = STACK_POINTER_BASE;
  mImpl->mStatusReg = {};
  // We can leave the stack as is
}

bool Processor::hasTrap() const {
  return mImpl->mStatusReg.mT;
}

u32& Processor::getRegister(u8 index) {
  if (index >= 16) {
    std::cerr << "Error: Processor::getRegister: Index out of bounds";

    std::abort();
  }

  return mImpl->mRegisters[index];
}

u32& Processor::getRegister(Register reg) {
  return getRegister(static_cast<u8>(reg));
}

u32 Processor::getRegister(u8 index) const {
  if (index >= 16) {
    std::cerr << "Error: Processor::getRegister: Index out of bounds";

    std::abort();
  }

  return mImpl->mRegisters[index];
}

u32 Processor::getRegister(Register reg) const {
  return getRegister(static_cast<u8>(reg));
}

StatusRegister& Processor::getStatusRegister() {
  return mImpl->mStatusReg;
}

StatusRegister Processor::getStatusRegister() const {
  return mImpl->mStatusReg;
}

MemStack& Processor::getStack() {
  return *mImpl->mStack;
}

const MemStack& Processor::getStack() const {
  return *mImpl->mStack;
}

void Processor::dump() const {
  std::cout << "Current Instruction: \n";
  if (mImpl->mCurrentInstr) {
    mImpl->mCurrentInstr->print(0);
  } else {
    std::cout << "<program not running>\n";
  }

  std::cout << "Registers:\n";
  for (u8 r = 0; r < 16; ++r) {
    Register reg = static_cast<Register>(r);
    u32 value = getRegister(reg);

    std::cout << std::setw(8)
              << to_string(reg)
              << "  0x"
              << std::hex << std::setfill('0')
              << std::setw(8) << value
              << std::dec << std::setfill(' ');

    if (reg == Register::SP) {
      std::cout << " [offset:"
                << (STACK_POINTER_BASE - value)
                << "]";
    } else if (reg == Register::LR || reg == Register::PC) {
      std::cout << " [label:"
                << resolveLabelName(static_cast<u16>(value >> 16))
                << " instr:0x"
                << std::hex << std::setfill('0')
                << std::setw(4) << (value & ((1 << 16) - 1))
                << std::dec << std::setfill(' ')
                << "]";
    } else {
      std::cout << " [dec:"
                << value
                << "]";

    }

    std::cout << '\n';
  }

  /*
  std::cout << "Status Register:\n";
  std::cout << std::boolalpha;
  std::cout << std::setw(22) << "N (Negative Bit) : " << getStatusRegister().mN << '\n';
  std::cout << std::setw(22) << "Z (Zero Bit)     : " << getStatusRegister().mZ << '\n';
  std::cout << std::setw(22) << "C (Carry Bit)    : " << getStatusRegister().mC << '\n';
  std::cout << std::setw(22) << "V (Overflow Bit) : " << getStatusRegister().mV << '\n';
  std::cout << std::setw(22) << "T (Trap Bit)     : " << getStatusRegister().mT << '\n';
  std::cout << std::noboolalpha;
  std::cout << std::endl;
  */

  mImpl->mStack->dump(getRegister(Register::SP));

  std::cout << std::endl;
}

std::string Processor::resolveLabelName(u16 labelIdx) const {
  const LabelAST* label = mImpl->mProgram->getLabelByIndex(labelIdx);
  std::ostringstream oss;
  if (label) {
    oss << label->getLabelName();
  } else if (labelIdx == std::numeric_limits<u16>::max()) {
    oss << "<reserved>";
  } else {
    oss << "<unknown:0x" << std::hex << labelIdx << std::dec << ">";
  }
  return oss.str();
}

bool Processor::hasTerminated() const {
  return (getRegister(Register::PC) >> 16) == std::numeric_limits<u16>::max() || hasTrap();
}


