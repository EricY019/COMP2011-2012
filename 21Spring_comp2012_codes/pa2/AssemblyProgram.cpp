#include "AssemblyProgram.h"

#include <iostream>
#include <string>

#include "MemStack.h"
#include "Processor.h"
#include "Program.h"
#include "Register.h"
#include "Util.h"

namespace {
/**
 * \brief Tests a given program.
 *
 * \param input The input program.
 * \param setup Additional setup to perform before running the instruction.
 * \param expected The expected value of a register or stack memory location after execution.
 * \param actualExpr The expression to execute to obtain the actual value of the register or stack memory location.
 * \param cmpValueName The name of the register or stack memory location under assertion.
 * \return `true` if the test passed.
 */
bool testProgram(
    const std::string& input,
    void(* setup)(Processor&),
    u32 expected,
    u32(* actualExpr)(const Processor&),
    const std::string& cmpValueName
) {
  Program program{input};
  Processor processor{};
  processor.loadProgram(program);

  setup(processor);

  processor.stepInstruction();

  const u32 actual = actualExpr(processor);

  if (expected != actual) {
    std::cout << "FAILED: Expected " << cmpValueName << "=" << expected << ", Got " << actual << std::endl;
    return false;
  }

  std::cout << "PASSED" << std::endl;
  return true;
}
}  // namespace

const std::string progReturns = R"(
main:
        sub     sp, sp, #4
        mov     r0, #0
        str     r0, [sp]
        mov     r0, #1        @ <-- Edit the immediate value (#1) to test different return values.
        add     sp, sp, #4
        bx      lr
)";

const std::string progTwoNumMax = R"(
max(int_int):
        sub     sp, sp, #12
        str     r0, [sp, #8]
        str     r1, [sp, #4]
        ldr     r0, [sp, #8]
        ldr     r1, [sp, #4]
        cmp     r0, r1
        ble     .LBB0_2
        b       .LBB0_1
.LBB0_1:
        ldr     r0, [sp, #8]
        str     r0, [sp]
        b       .LBB0_3
.LBB0_2:
        ldr     r0, [sp, #4]
        str     r0, [sp]
        b       .LBB0_3
.LBB0_3:
        ldr     r0, [sp]
        add     sp, sp, #12
        bx      lr
main:
        push    {r11, lr}
        mov     r11, sp
        sub     sp, sp, #16
        mov     r0, #0
        str     r0, [r11, #-4]
        mov     r0, #1          @ <-- Edit the immediate value (#1) to change the first argument to max()
        str     r0, [sp, #8]
        mov     r0, #2          @ <-- Edit the immediate value (#2) to change the second argument to max()
        str     r0, [sp, #4]
        ldr     r0, [sp, #8]
        ldr     r1, [sp, #4]
        bl      max(int_int)
        mov     sp, r11
        pop     {r11, lr}
        bx      lr
)";

const std::string progIterativeAdd = R"(
sum(int):
        sub     sp, sp, #12
        str     r0, [sp, #8]
        mov     r0, #0
        str     r0, [sp, #4]
        str     r0, [sp]
        b       .LBB0_1
.LBB0_1:
        ldr     r0, [sp]
        ldr     r1, [sp, #8]
        cmp     r0, r1
        bge     .LBB0_4
        b       .LBB0_2
.LBB0_2:
        ldr     r0, [sp]
        ldr     r1, [sp, #4]
        add     r0, r1, r0
        str     r0, [sp, #4]
        b       .LBB0_3
.LBB0_3:
        ldr     r0, [sp]
        add     r0, r0, #1
        str     r0, [sp]
        b       .LBB0_1
.LBB0_4:
        ldr     r0, [sp, #4]
        add     sp, sp, #12
        bx      lr
main:
        push    {r11, lr}
        mov     r11, sp
        sub     sp, sp, #8
        mov     r0, #0
        str     r0, [sp, #4]
        mov     r0, #10         @ <-- Edit the immediate value (#10) to test different summation limits.
        bl      sum(int)
        mov     sp, r11
        pop     {r11, lr}
        bx      lr
)";

const std::string progRecursiveAdd = R"(
sum(int):
        push    {r11, lr}
        mov     r11, sp
        sub     sp, sp, #16
        str     r0, [sp, #8]
        ldr     r0, [sp, #8]
        cmp     r0, #0
        bgt     .LBB0_2
        b       .LBB0_1
.LBB0_1:
        mov     r0, #0
        str     r0, [r11, #-4]
        b       .LBB0_3
.LBB0_2:
        ldr     r0, [sp, #8]
        sub     r1, r0, #1
        str     r0, [sp, #4]
        mov     r0, r1
        bl      sum(int)
        ldr     r1, [sp, #4]
        add     r0, r1, r0
        str     r0, [r11, #-4]
        b       .LBB0_3
.LBB0_3:
        ldr     r0, [r11, #-4]
        mov     sp, r11
        pop     {r11, lr}
        bx      lr
main:
        push    {r11, lr}
        mov     r11, sp
        sub     sp, sp, #8
        mov     r0, #0
        str     r0, [sp, #4]
        mov     r0, #10         @ <-- Edit the immediate value (#10) to test different summation limits.
        bl      sum(int)
        mov     sp, r11
        pop     {r11, lr}
        bx      lr
)";

bool testNopProgram() {
  static const std::string prog = R"(
main:
        nop
)";

  return testProgram(
      prog,
      [](Processor&) {},
      0,
      [](const Processor& p) { return p.getRegister(Register::R0); },
      "r0"
  );
}

bool testMovProgram() {
  static const std::string prog = R"(
main:
        mov       r0, r1
)";

  return testProgram(
      prog,
      [](Processor& p) {
        p.getRegister(Register::R1) = 1;
      },
      1,
      [](const Processor& p) { return p.getRegister(Register::R0); },
      "r0"
  );
}

bool testStrProgram() {
  static const std::string prog = R"(
main:
        str       r0, [sp]
)";

  return testProgram(
      prog,
      [](Processor& p) {
        p.getRegister(Register::R0) = 1;
        p.getRegister(Register::SP) -= 4;
      },
      1,
      [](const Processor& p) { return p.getStack().load(p.getRegister(Register::SP)); },
      "[sp]"
  );
}

bool testLdrProgram() {
  static const std::string prog = R"(
main:
        ldr       r0, [sp]
)";

  return testProgram(
      prog,
      [](Processor& p) {
        p.getRegister(Register::SP) -= 4;
        p.getStack().store(1, p.getRegister(Register::SP));
      },
      1,
      [](const Processor& p) { return p.getRegister(Register::R0); },
      "r0"
  );
}

bool testPushProgram() {
  static const std::string prog = R"(
main:
        push      {r0, r1}
)";

  bool test1 = testProgram(
      prog,
      [](Processor& p) {
        p.getRegister(Register::R0) = 1;
        p.getRegister(Register::R1) = 2;
      },
      1,
      [](const Processor& p) { return p.getStack().load(p.getRegister(Register::SP)); },
      "sp"
  );
  bool test2 = testProgram(
      prog,
      [](Processor& p) {
        p.getRegister(Register::R0) = 1;
        p.getRegister(Register::R1) = 2;
      },
      2,
      [](const Processor& p) { return p.getStack().load(p.getRegister(Register::SP) + 4); },
      "[sp+0x4]"
  );

  return test1 && test2;
}

bool testPopProgram() {
  static const std::string prog = R"(
main:
        pop      {r0, r1}
)";

  bool test1 = testProgram(
      prog,
      [](Processor& p) {
        p.getRegister(Register::SP) -= 8;
        p.getStack().store(1, p.getRegister(Register::SP));
        p.getStack().store(2, p.getRegister(Register::SP) + 4);
      },
      1,
      [](const Processor& p) { return p.getRegister(Register::R0); },
      "r0"
  );
  bool test2 = testProgram(
      prog,
      [](Processor& p) {
        p.getRegister(Register::SP) -= 8;
        p.getStack().store(1, p.getRegister(Register::SP));
        p.getStack().store(2, p.getRegister(Register::SP) + 4);
      },
      2,
      [](const Processor& p) { return p.getRegister(Register::R1); },
      "r1"
  );

  return test1 && test2;
}

bool testAddProgram() {
  static const std::string prog = R"(
main:
        add       r0, r0, r1
)";

  return testProgram(
      prog,
      [](Processor& p) {
        p.getRegister(Register::R0) = 1;
        p.getRegister(Register::R1) = 2;
      },
      3,
      [](const Processor& p) { return p.getRegister(Register::R0); },
      "r0"
  );
}

bool testSubProgram() {
  static const std::string prog = R"(
main:
        sub       r0, r0, r1
)";

  return testProgram(
      prog,
      [](Processor& p) {
        p.getRegister(Register::R0) = 2;
        p.getRegister(Register::R1) = 1;
      },
      1,
      [](const Processor& p) { return p.getRegister(Register::R0); },
      "r0"
  );
}
