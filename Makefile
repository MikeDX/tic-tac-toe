CC=gcc
CFLAGS=-I../include

all: tic-tac-toe

tic-tac-toe: tic-tac-toe.o
	$(CC) -o tic-tac-toe tic-tac-toe.o

tic-tac-toe.o: tic-tac-toe.c
	$(CC) -c tic-tac-toe.c $(CFLAGS)

clean:
	rm -f *.o tic-tac-toe
