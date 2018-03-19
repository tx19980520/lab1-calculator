main.exe:filter.o calculator.o main.o
	g++ -o main.exe filter.o calculator.o main.o
	
filter.o: filter.cpp filter.h
	g++ -c filter.cpp
calculator.o: calculator.cpp calculator.h
	g++ -c calculator.cpp
main.o: main.cpp filter.h calculator.h
	g++ -c main.cpp