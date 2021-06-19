CPPFLAGS = -std=c++11
all: hero.exe

hero.exe: thing.o cell.o game.o main.cpp
	g++ -o $@ $(CPPFLAGS) thing.o cell.o game.o main.cpp

%.o: %.cpp
	g++ $(CPPFLAGS) -c $< -o $@ 

clean:
	del  *.o *.exe