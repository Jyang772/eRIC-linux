CC=gcc
CFLAGS=-Wall

test: main.o
	+$(MAKE) -C util
	$(CC) main.o util/util.o util/interface.o util/readLine.o util/safe_handle.o util/packet.o util/crc.o -o test

main.o: main.c
	$(CC) -c main.c

clean:
	$(MAKE) clean -C util
	rm -f *.o test
