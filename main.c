#include "util/util.h"

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>




int main() {


	//Determine which /dev/ file is the device on
	char* name = "A";
	char* portname = "/dev/ttyUSB0";
	int fd = 0;
	int wlen = 0;
	int BAUD_RATE = B19200;

	//Define and Initiate Radio Structs
	/*
	Radio radA = {
		.ID = "A",
		.setDestination = setDestination
	};
	*/

	Radio* radA = init_Radio(name);
	setup_interface(radA, &fd, portname, BAUD_RATE);

	printf("Name: %s\n",radA->ID);
	radA->setDestination(radA,"B");
	printf("Destination: %s\n",radA->destAddr);

	//radA->init_connection();
	//radA->sendCmd("CMD");
	//radA->getTemp();
	//radA->close_connection();

}
