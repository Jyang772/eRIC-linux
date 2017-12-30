CC=gcc
CFLAGS=-Wall

test: 
	+$(MAKE) -C util
	+$(CC) main.o util/util.o util/interfaces.o -o test

main.o: main.c
	$(CC) -c main.c

clean:
	rm *.o test
