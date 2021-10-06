prog: main.o Board.o Executive.o 
	g++ -std=c++11 -g -Wall main.o Executive.o Board.o -o prog

main.o: main.cpp
	g++ -std=c++11 -g -Wall -c main.cpp

Executive.o: Executive.h Executive.cpp
	g++ -std=c++11 -g -Wall -c Executive.cpp Executive.h

Board.o: Board.h Board.cpp
	g++ -std=c++11 -g -Wall -c Board.cpp Board.h

clean: 
	rm -fr *.o prog prog.* Board.h.gch Executive.h.gch
