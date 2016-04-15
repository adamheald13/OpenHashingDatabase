Project02: main.o Record.o Database.o
	g++ -g main.o Record.o Database.o -o Project02
main.o: main.cpp
	g++ -g -c main.cpp
Record.o: Record.cpp Record.h
	g++ -g -c Record.cpp
Database.o: Database.cpp Database.h
	g++ -g -c Database.cpp
clean:
	rm *.o Project02
