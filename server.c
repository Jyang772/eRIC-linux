#include "util/util.h"
#include <stdio.h>
#include <stdlib.h>



int main() {


	char* name = "B";
	char* portname = "/dev/ttyUSB0";
	int fd = 0;
	int wlen = 0;
	int BAUD_RATE = B19200;

	//Initiate Radio in server mode
	Radio* radB = init_Radio(name);
	setup_interface(%fd, portname, BAUD_RATE);

	radB.listen();
}
