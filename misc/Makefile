CC=gcc
CFLAGS=-Wall

test: server.o
	+$(MAKE) -C ../util
	$(CC) server.o ../util/util.o ../util/interface.o ../util/packet.o ../util/crc.o ../util/readLine.o ../util/safe_handle.o -o server

server.o: server.c
	$(CC) -c server.c

clean:
	$(MAKE) clean -C ../util
	rm -f *.o server
