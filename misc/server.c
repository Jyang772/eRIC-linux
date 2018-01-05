#include "../util/util.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>



int main() {

	char* name = "B";
	char* portname = "/dev/ttyUSB0";
	int fd = 0;
	int wlen = 0;
	int BAUD_RATE = B19200;

	//Initiate Radio in server mode
	Radio* radB = init_Radio(name);
	setup_interface(radB, &fd, portname, BAUD_RATE);
	radB->setDestination(radB, "A");

	radB->listen(radB);
}
