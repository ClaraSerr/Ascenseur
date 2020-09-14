main : main.o elevator.o person.o
	gcc -o main main.o elevator.o person.o -lncurses

main.o : main.c elevator.h person.h
	gcc -o main.o -c main.c -lncurses

elevator.o: elevator.c elevator.h person.h 
	gcc -o elevator.o -c elevator.c -lncurses

person.o: person.c person.h 
	gcc -o person.o -c person.c -lncurses

clean :
	rm -f *.o