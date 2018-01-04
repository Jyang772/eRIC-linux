#include "util/util.h"

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <poll.h>

struct pollfd fds[1];
int timeout;

int main() {


	//Determine which /dev/ file is the device on
	char* name = "A";
	char* portname = "/dev/ttyUSB1";
	int fd = 0;
	int wlen = 0;
	int BAUD_RATE = B19200;


	Radio* radA = init_Radio(name);
	setup_interface(radA, &fd, portname, BAUD_RATE);

	printf("Name: %s\n",radA->ID);
	radA->setDestination(radA,"B");
	printf("Destination: %s\n",radA->destAddr);

	/* Todo: Poll init function */	
	fds[0].fd = fd;
	fds[0].events = 0;
	fds[0].events |= POLLIN;
	timeout = 1000;
	int pret;
	int bytes;

	while(1) {
		radA->init_connection(radA);
		pret = poll(fds, 1, timeout);
		if(pret == 0) {
			printf("ret %d\n",pret);
			printf("\ttimeout\n");
		}
		else {
			Packet data;
			int rd = safe_read(fd, &data, sizeof(Packet)); /* Check for errors */
			
			if(rd > 0)
				printf("d: %s\n",data.type);
		}	
		sleep(1); /* Allow time for node to transmit reply */
	}

	//radA->sendCmd("CMD");
	//radA->getTemp();
	//radA->close_connection();
	//
	//
	
	/*
	if(strcmp(data.type,"0000") == 0)
		printf("Type 1\n");

	printf("Size of packet: %d\n",sizeof(data));

	printf("%s\n",data.srcAddr);
	free_packet(&data);
	printf("%s\n",data.srcAddr);
	*/


	/*
	Packet data;
	strcpy(data.type,"0000");
	strcpy(data.srcAddr,"A");
	strcpy(data.destAddr,"B");
	strcpy(data.payload,"lol");

	write_data(&data);
	read_data();
	strcpy(data.type,"s");
	write_data(&data);
	read_data();
	strcpy(data.type, "end");
	write_data(&data);
	read_data();
*/	

}
