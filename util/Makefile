CC=gcc
CFLAGS=-Wall

all: util.o interface.o packet.o crc.o safe_handle.o

util.o: util.c
	$(CC) -c util.c

interfaces.o: interface.c
	$(CC) -c interface.c

packet.o: packet.c
	$(CC) -c packet.c 

crc.o: crc.c
	$(CC) -c crc.c

safe_handle.o: safe_handle.c
	$(CC) -c safe_handle.c

clean:
	rm -f *.o
