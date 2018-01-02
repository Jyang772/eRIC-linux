#include "util.h"
#include "interface.h"

void setDestination(Radio* r, char* s) {

	printf("setDestination\n");

	r->destAddr = strdup(s);
	assert(strcmp(r->destAddr,s) == 0);
	return;
}

int init_connection(Radio* r) {
	//Send connection request
	//Construct Connection request packet
	Packet data = { 
	
	};
	
	if(send(r, data) > 0)
		return 1;
	else
		return -1;
}

int send(Radio* r, Packet data) {

	int wlen;
	int fd;
	fd = r->fd;

	wlen = write(fd, &data, sizeof(data));
	if(wlen != sizeof(data)) {
		printf("Error from write: %d, %d\n", wlen, errno);
	}
}

void listen(Radio* r, char* s) {
/*
	while(1) {
		unsigned char buf[80];
		int rdlen;
		
		rdlen = readLine(fd, buf, sizeof(buf));
		printf("Command read: %s\n",buf);

	}
	*/

}

int setup_interface(Radio* r, int* fd, char* portname, int BAUD_RATE) {

	*fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
	if(*fd < 0) {
		printf("Error opening %s: %s\n", portname, strerror(errno));
		return -1;
	}

	set_interface_attribs(*fd, BAUD_RATE);
	r->fd = *fd;

	return 1;
}

Radio* init_Radio(char* name) {

	Radio* new_Radio = (Radio*)malloc(sizeof(Radio));

	new_Radio->ID = strdup(name);
	new_Radio->setDestination = setDestination;

	return new_Radio;
}

int getTemp(Radio* r, char* s) {

}

