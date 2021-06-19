OBJS	= main.o given.o todo.o
PROG	= pa3
HEAD	= given.h todo.h

$(PROG): $(OBJS)
	g++ -o $(PROG) $(OBJS)

main.o: main.cpp $(HEAD)
	g++ -c main.cpp

given.o: given.cpp $(HEAD)
	g++ -c given.cpp

todo.o: todo.cpp $(HEAD)
	g++ -c todo.cpp

clean:
	del *.o
	del *.exe