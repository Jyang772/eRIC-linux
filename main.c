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

	Packet data;

	/* Handshake */
	if(radA->init_connection(radA) < 0) {
		printf("Error establishing connection to node: %s\n",radA->destAddr);
		exit(1);
	}
	
	/* Repeatedly request temperature from Node B */
	while(1) {
		while(radA->getTemp(radA) < 0);
		sleep(1);
	}
	return 0;



	//radA->sendCmd("CMD");
	//radA->getTemp();
	//radA->close_connection();
}
