project: user_interface.o database.o
	gcc -o project user_interface.o database.o

user_interface.o: user_interface.c database.h record.h
	gcc -c -pedantic-errors -Wall -std=c99 user_interface.c

database.o: database.c database.h record.h
	gcc -c -pedantic-errors -Wall -std=c99 database.c
