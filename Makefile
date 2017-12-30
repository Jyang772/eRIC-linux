CC=gcc
CFLAGS=-Wall

test: main.o
	+$(MAKE) -C util
	$(CC) main.o util/util.o util/interface.o -o test

test-build: main.o util/util.o util/interface.o
	$(CC) main.o util/util.o util/interface.o -o test

main.o: main.c
	$(CC) -c main.c

clean:
	+$(MAKE) clean -C util
	rm *.o test
