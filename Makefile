
cwordle: main.o board.o
	gcc main.o board.o -o cwordle

main.o: main.o board.h
	gcc -Wall -g -c main.c

board.o: board.c board.h
	gcc -Wall -g -c board.c

clean:
	rm -f *.o cwordle


