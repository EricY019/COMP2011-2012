CPPS := $(wildcard *.cpp)
CPPS := $(filter-out main.cpp, $(CPPS))
OBJS := $(CPPS:.cpp=.o)

# Use -DDEBUG to enable debugging, you may also write your own debuggings
# FLAGS='-DDEBUG -std=c++11'

FLAGS='-std=c++11'

default: pa4.exe

%.o: %.cpp
	g++ -c $< -o $@ $(FLAGS)

pa4.exe: $(OBJS) main.cpp
	g++ $^ $(FLAGS) -o $@

clean:
	del *.o pa4.exe

