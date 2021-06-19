#include <iostream>

#include "AssemblyProgram.h"
#include "Opcode.h"
#include "Processor.h"
#include "Program.h"
#include "Register.h"

int main(int argc, const char* argv[]) {
  // Run the supplied given test cases if there is a command-line argument.
  if (argc == 2) {
    const std::string arg = argv[1];

    bool(* testFunc)() = nullptr;
    if (arg == to_string(Op::NOP)) {
      testFunc = &testNopProgram;
    } else if (arg == to_string(Op::MOV)) {
      testFunc = &testMovProgram;
    } else if (arg == to_string(Op::STR)) {
      testFunc = &testStrProgram;
    } else if (arg == to_string(Op::LDR)) {
      testFunc = &testLdrProgram;
    } else if (arg == to_string(Op::PUSH)) {
      testFunc = &testPushProgram;
    } else if (arg == to_string(Op::POP)) {
      testFunc = &testPopProgram;
    } else if (arg == to_string(Op::ADD)) {
      testFunc = &testAddProgram;
    } else if (arg == to_string(Op::SUB)) {
      testFunc = &testSubProgram;
    } else {
      std::cout << "Unknown test program " << arg << std::endl;
      return 2;
    }

    return !testFunc();
  }

  // Paste your assembly within the brackets.
  // Alternatively, use one of the provided programs in AssemblyPrograms.h.
  const std::string input = R"(
main:
        sub     sp, sp, #4
        mov     r0, #0
        str     r0, [sp]
        mov     r0, #1        @ <-- Edit the immediate value (#1) to test different return values.
        add     sp, sp, #4
        bx      lr
)";

  Program program{input};
  if (!program.isValid()) {  // We quit if the program is not valid.
    return 1;
  }

  // Uncomment the following line to see the entire AST of the program.
  // program.printAST();

  // To enable debug mode, pass `true` to the first parameter of the Processor constructor.
  Processor processor(false);

  // Load the program into our processor.
  processor.loadProgram(program);

  // Run the program until it terminates.
  processor.run();
  // Alternatively you can use the following, which executes each instruction one-by-one until the program exits.
  // while (!processor.hasTerminated()) {
  //  processor.stepInstruction();
  // }

  if (processor.hasTrap()) {
    // If the processor terminates because of a trap, it means that something went wrong.
    // Output the state of the processor for debugging.
    std::cout << "Error while executing the program." << std::endl;
    std::cout << "State of processor on error:" << std::endl;
    processor.dump();
  } else {
    // The return value of functions is
    std::cout << processor.getRegister(Register::R0) << std::endl;
  }
}
