CC=gcc
CFLAGS=-g -pedantic -std=c99 -Wall -Wextra

all: test

bintree: bintree.o
	$(CC) $(CFLAGS) bintree.o -o bintree

bintree.o: bintree.c bintree.h
	$(CC) $(CFLAGS) -c bintree.c

test: test.o
	$(CC) $(CFLAGS) test.o -o test

test.o: bintree.o
	$(CC) $(CFLAGS) -c test.c

clean:
	rm -f *.o
	rm -f test
