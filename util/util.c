#include "util.h"
#include "interface.h"

void setDestination(Radio* r, char* s) {

	r->destAddr = strdup(s);
	assert(strcmp(r->destAddr,s) == 0);
	return;
}

void init_Radio(int fd, int BAUD_RATE) {

	set_interface_attribs(fd, BAUD_RATE);
}
