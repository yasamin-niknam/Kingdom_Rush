a.out: rsdl.o functions.o main.o
	g++  rsdl.o functions.o main.o -lSDL2 -lSDL2_image -lSDL2_ttf

rsdl.o: rsdl.hpp rsdl.cpp
	g++ -c rsdl.cpp -o rsdl.o

main.o: main.cpp functions.o
	g++ -c main.cpp -o main.o

functions.o: functions.cpp functions.hpp rsdl.o
	g++ -c functions.cpp -o functions.o

clean:
	rm -r *.o