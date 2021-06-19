AR := ar
CXX := g++
STRIP := strip
CXXFLAGS = -std=c++11 -pedantic-errors -Werror=pedantic -Wall -Wextra -g

LIB_OBJS = \
		AST.o \
		BranchInstructionAST.o \
		BranchInstructionASTParsing.o \
		BranchInstructionASTPrinting.o \
		InstructionASTParsing.o \
		InstructionASTPrinting.o \
		LabelAST.o \
		LabelASTPrinting.o \
		MemStack.o \
		Opcode.o \
		OperandAST.o \
		OperandASTParsing.o \
		OperandASTPrinting.o \
		Processor.o \
		Program.o \
		Register.o \
		Strings.o

MAIN_OBJS = AssemblyProgram.o InstructionAST.o main.o libcomp2012pa2.a

.DEFAULT_GOAL := all

$(LIB_OBJS): CXXFLAGS += -O2

all: pa2

pa2: $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) -o $@.exe $(MAIN_OBJS)

libcomp2012pa2.a: $(LIB_OBJS)
	$(AR) rs $@ $^
	$(STRIP) -S $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I. -Iinclude -c $^ -o $@

clean:
	del *.a pa2*.exe *.o

clean-pa2:
	del AssemblyProgram.o InstructionAST.o main.o
