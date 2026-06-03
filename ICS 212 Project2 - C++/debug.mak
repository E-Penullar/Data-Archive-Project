project_debug: user_interface.o llist.o
	g++ -o project_debug user_interface.o llist.o -DDEBUG

user_interface.o: user_interface.cpp llist.h record.h
	g++ -c -pedantic-errors -Wall -ansi user_interface.cpp -DDEBUG

llist.o: llist.cpp llist.h record.h
	g++ -c -pedantic-errors -Wall -ansi llist.cpp -DDEBUG
