#include "util.h"
#include "interface.h"

void setDestination(Radio* r, char* s) {

	printf("setDestination\n");

	r->destAddr = strdup(s);
	assert(strcmp(r->destAddr,s) == 0);
	return;
}

int setup_interface(int* fd, char* portname, int BAUD_RATE) {

	*fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
	if(*fd < 0) {
		printf("Error opening %s: %s\n", portname, strerror(errno));
		return -1;
	}

	set_interface_attribs(*fd, BAUD_RATE);
}

Radio* init_Radio(char* name) {


	Radio* new_Radio = (Radio*)malloc(sizeof(Radio));

	new_Radio->ID = strdup(name);
	new_Radio->setDestination = setDestination;

	return new_Radio;
}
