project: user_interface.o llist.o
	g++ -o project user_interface.o llist.o

user_interface.o: user_interface.cpp llist.h record.h
	g++ -c -pedantic-errors -Wall -ansi user_interface.cpp

llist.o: llist.cpp llist.h record.h
	g++ -c -pedantic-errors -Wall -ansi llist.cpp

